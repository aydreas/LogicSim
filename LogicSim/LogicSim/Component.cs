using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace LogicSim
{
    abstract class Component
    {
        private Input[] _Inputs;
        private Output[] _Outputs;
        public readonly int Index;

        public Input[] Inputs
        {
            get
            {
                return _Inputs;
            }
            private set
            {
                if ((value ?? throw new ArgumentNullException("Inputs")).Length != InputCount)
                    throw new ArgumentException("Array must be of same length as InputCount");
                _Inputs = value;
            }
        }

        public Output[] Outputs
        {
            get
            {
                return _Outputs;
            }
            private set
            {
                if ((value ?? throw new ArgumentNullException("Outputs")).Length != OutputCount)
                    throw new ArgumentException("Array must be of same length as OutputCount");
                _Outputs = value;
            }
        }

        public abstract int InputCount { get; }
        public abstract int OutputCount { get; }

        public abstract void Compute();

        /// <summary>
        /// Initializes component
        /// </summary>
        /// <param name="inputs">Inputs for component</param>
        /// <param name="outputs">Outputs for component</param>
        /// <param name="index">Index of component, required for multithreading</param>
        protected Component(Input[] inputs, Output[] outputs, int index)
        {
            Inputs = inputs;
            Outputs = outputs;
            Index = index;
        }

        /// <summary>
        /// Initializes component based on provided links and creates data correlations between links and component
        /// </summary>
        /// <param name="inputs">Inputs for component as links</param>
        /// <param name="outputs">Outputs for component as links</param>
        /// <param name="index">Index of component, required for multithreading</param>
        protected Component(Link[] inputs, Link[] outputs, int index)
        {
            Inputs = inputs.Select(x => new Input(this, x)).ToArray();
            Outputs = outputs.Select(x => new Output(this, x)).ToArray();
            Index = index;

            foreach(Input i in Inputs)
                i.Link.Inputs = i.Link.Inputs.Append(i).ToArray();
            foreach (Output o in Outputs)
                o.Link.Outputs = o.Link.Outputs.Append(o).ToArray();
        }
    }
}
