using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    class Input : IConnection
    {
        private Component _Component;
        private Link _Link;
        public bool Powered { get => Link.Powered; }

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

        public Input()
        {

        }

        public Input(Component component)
        {
            Component = component;
        }

        public Input(Link link)
        {
            Link = link;
        }

        public Input(Component component, Link link)
        {
            Component = component;
            Link = link;
        }
    }
}
