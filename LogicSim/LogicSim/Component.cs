using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    abstract class Component
    {
        private Input[] _Inputs;
        private Output[] _Outputs;

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
                if ((value ?? throw new ArgumentNullException("Outputs")).Length != InputCount)
                    throw new ArgumentException("Array must be of same length as OutputCount");
                _Outputs = value;
            }
        }

        public abstract int InputCount { get; }
        public abstract int OutputCount { get; }

        public abstract void Compute();

        protected Component(Input[] inputs, Output[] outputs)
        {
            Inputs = inputs;
            Outputs = outputs;
        }
    }
}
