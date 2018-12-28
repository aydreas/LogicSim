using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace LogicSim
{
    static class Board
    {
        public enum State
        {
            Uninitialized = 0,
            Initialized = 1,
            Paused = 2,
            Running = 3
        }

        public static State CurrentState { get; private set; }

        public static int THREADNUM { get; private set; }
        public static bool SYNCHRONIZEDEXECUTION { get; private set; }

        public static Component[] Components { get; private set; }

        private static bool[] Buffer1;
        private static bool[] Buffer2;

        public static bool[] ReadBuffer;
        public static bool[] WriteBuffer;

        private static Thread[] WorkerThreads = new Thread[THREADNUM];

        private static Barrier WorkerBarrier = new Barrier(THREADNUM, (a) =>
        {
            while(CurrentState == State.Paused)
            {
                Thread.Sleep(1000);
            }

            bool[] readBuffer = ReadBuffer;
            ReadBuffer = WriteBuffer;
            WriteBuffer = readBuffer;
            for (int i = 0; i < WriteBuffer.Length; i++)
            {
                WriteBuffer[i] = false;
            }

            if(SYNCHRONIZEDEXECUTION)
            {
                //TODO: wait for next tick confirmation from network
                Thread.Sleep(1000);
            }
        });

        public static void Init(Component[] components)
        {
            if (CurrentState != State.Uninitialized)
                throw new InvalidOperationException("Board can only be initialized once!");

            THREADNUM = 1;
            SYNCHRONIZEDEXECUTION = false;

            string[] args = Environment.GetCommandLineArgs();
            if(args.Contains("--threads"))
            {
                string threadsString = args.SkipWhile(x => !x.Equals("--threads")).ElementAtOrDefault(1);
                if(threadsString != null)
                {
                    try
                    {
                        THREADNUM = Int32.Parse(threadsString);
                    } catch(FormatException) { }
                }
            }
            if (args.Contains("--synchronized"))
                SYNCHRONIZEDEXECUTION = true;

            Components = components ?? throw new ArgumentNullException("components");

            Buffer1 = new bool[Components.Length];
            Buffer2 = new bool[Components.Length];

            ReadBuffer = Buffer1;
            WriteBuffer = Buffer2;

            for(int i = 0; i < THREADNUM; i++)
            {
                WorkerThreads[i] = new Thread(() => Worker(i));
            }

            CurrentState = State.Initialized;
        }

        public static void Start()
        {
            switch (CurrentState)
            {
                case State.Uninitialized:
                    throw new InvalidOperationException("Board not initialized!");
                case State.Paused:
                    CurrentState = State.Running;
                    break;
                case State.Running:
                    throw new InvalidOperationException("Simulation is already running!");
                case State.Initialized:
                    foreach (Thread t in WorkerThreads)
                        t.Start();
                    break;
                default:
                    throw new InvalidOperationException("Board is not in correct state!");
            }
        }

        public static void Pause()
        {
            switch (CurrentState)
            {
                case State.Uninitialized:
                    throw new InvalidOperationException("Board not initialized!");
                case State.Paused:
                    throw new InvalidOperationException("Board already paused!");
                case State.Initialized:
                    throw new InvalidOperationException("Simulation is not running!");
                case State.Running:
                    CurrentState = State.Paused;
                    break;
                default:
                    throw new InvalidOperationException("Board is not in correct state!");
            }
        }

        private static void Worker(int index)
        {
            while (true)
            {
                for (int i = index; i < ReadBuffer.Length; i += THREADNUM)
                {
                    if (ReadBuffer[i])
                        Components[i].Compute();
                }
                WorkerBarrier.SignalAndWait();
            }
        }
    }
}
