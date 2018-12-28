using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace LogicSim
{
    static class Board
    {
        public static int THREADNUM { get; private set; }
        public static bool SYNCHRONIZEDEXECUTION { get; private set; }

        public static Component[] Components { get; private set; }

        private static bool[] Buffer1;
        private static bool[] Buffer2;

        public static bool[] ReadBuffer;
        public static bool[] WriteBuffer;

        private static Thread[] Threads = new Thread[THREADNUM];

        private static Barrier WorkerBarrier = new Barrier(THREADNUM, (a) =>
        {
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
            if (Threads != null)
                throw new NotImplementedException();

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
        }

        public static void Worker(int index)
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
