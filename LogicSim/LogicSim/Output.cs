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

        public Output()
        {

        }

        public Output(Component component)
        {
            Component = component;
        }

        public Output(Link link)
        {
            Link = link;
        }

        public Output(Component component, Link link)
        {
            Component = component;
            Link = link;
        }
    }
}
