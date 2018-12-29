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

        /// <summary>
        /// whether link is powered, determined by the power state of all outputs connected.
        /// </summary>
        public bool Powered
        {
            get
            {
                return Outputs.Any(x => x.Powered);
            }
        }

        /// <summary>
        /// all outputs connected to the link.
        /// </summary>
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

        /// <summary>
        /// all inputs connected to the link.
        /// </summary>
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

        /// <summary>
        /// creates a new link with no inputs and outputs.
        /// </summary>
        public Link()
        {
            Outputs = new Output[0];
            Inputs = new Input[0];
        }

        /// <summary>
        /// creates a new link with no inputs and specified outputs.
        /// </summary>
        /// <param name="outputs">outputs to add to the link</param>
        public Link(Output[] outputs)
        {
            Outputs = outputs;
        }

        /// <summary>
        /// creates a new link with specified inputs and no outputs.
        /// </summary>
        /// <param name="inputs">inputs to add to the link</param>
        public Link(Input[] inputs)
        {
            Inputs = inputs;
        }

        /// <summary>
        /// creates a new link with specified inputs and outputs.
        /// </summary>
        /// <param name="outputs">outputs to add to the link</param>
        /// <param name="inputs">inputs to add to the link</param>
        public Link(Output[] outputs, Input[] inputs)
        {
            Outputs = outputs;
            Inputs = inputs;
        }
    }
}
