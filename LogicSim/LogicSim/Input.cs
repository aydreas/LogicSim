using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    class Input : IConnection
    {
        private Component _Component;
        private Link _Link;

        /// <summary>
        /// whether input is powered.
        /// </summary>
        public bool Powered { get => Link.Powered; }

        /// <summary>
        /// Component connected to the input.
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
        /// Link associated to the input.
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
        /// Creates a new empty input.
        /// </summary>
        public Input()
        {

        }

        /// <summary>
        /// Creates a new input.
        /// </summary>
        /// <param name="component">Component connected to the input</param>
        public Input(Component component)
        {
            Component = component;
        }

        /// <summary>
        /// Creates a new input.
        /// </summary>
        /// <param name="link">Link associated to the input</param>
        public Input(Link link)
        {
            Link = link;
        }

        /// <summary>
        /// Creates a new input.
        /// </summary>
        /// <param name="component">Component connected to the input</param>
        /// <param name="link">Link associated to the input</param>
        public Input(Component component, Link link)
        {
            Component = component;
            Link = link;
        }
    }
}
