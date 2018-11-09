using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    class Output : IConnection
    {
        private Component _Component;
        private Link _Link;
        public bool Powered { get; set; }

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
