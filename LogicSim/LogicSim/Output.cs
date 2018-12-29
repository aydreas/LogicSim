using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    class Output : IConnection
    {
        private Component _Component;
        private Link _Link;
        private bool _Powered;

        /// <summary>
        /// whether output is powered.
        /// </summary>
        public bool Powered {
            get
            {
                return _Powered;
            }
            set
            {
                if (_Powered != value)
                {
                    foreach(Input input in Link.Inputs)
                    {
                        Board.WriteBuffer[input.Component.Index] = true;
                    }

                    _Powered = value;
                }
            }
        }

        /// <summary>
        /// Component connected to the output.
        /// </summary>
        public Component Component
        {
            get
            {
                return _Component;
            }
            private set
            {
                _Component = value ?? throw new ArgumentNullException("Component");
            }
        }

        /// <summary>
        /// Link associated to the output.
        /// </summary>
        public Link Link
        {
            get
            {
                return _Link;
            }
            private set
            {
                _Link = value ?? throw new ArgumentNullException("Link");
            }
        }

        /// <summary>
        /// Creates a new empty output.
        /// </summary>
        public Output()
        {

        }

        /// <summary>
        /// Creates a new output.
        /// </summary>
        /// <param name="component">Component connected to the output</param>
        public Output(Component component)
        {
            Component = component;
        }

        /// <summary>
        /// Creates a new output.
        /// </summary>
        /// <param name="link">Link associated to the output</param>
        public Output(Link link)
        {
            Link = link;
        }

        /// <summary>
        /// Creates a new output.
        /// </summary>
        /// <param name="component">Component connected to the output</param>
        /// <param name="link">Link associated to the output</param>
        public Output(Component component, Link link)
        {
            Component = component;
            Link = link;
        }
    }
}
