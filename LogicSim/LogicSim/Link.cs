using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace LogicSim
{
    class Link
    {
        private Output[] _Outputs;
        private Input[] _Inputs;

        public bool Powered
        {
            get
            {
                return Outputs.Any(x => x.Powered);
            }
        }

        public Output[] Outputs
        {
            get
            {
                return _Outputs;
            }
            set
            {
                _Outputs = value ?? throw new ArgumentNullException("Outputs");
            }
        }

        public Input[] Inputs
        {
            get
            {
                return _Inputs;
            }
            set
            {
                _Inputs = value ?? throw new ArgumentNullException("Inputs");
            }
        }

        public Link()
        {
            Outputs = new Output[0];
            Inputs = new Input[0];
        }

        public Link(Output[] outputs)
        {
            Outputs = outputs;
        }

        public Link(Input[] inputs)
        {
            Inputs = inputs;
        }

        public Link(Output[] outputs, Input[] inputs)
        {
            Outputs = outputs;
            Inputs = inputs;
        }
    }
}
