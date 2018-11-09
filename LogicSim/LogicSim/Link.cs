using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace LogicSim
{
    class Link
    {
        private IConnection[] _Connections;
        public bool Powered
        {
            get
            {
                return Connections.Any(x => x.Powered);
            }
        }

        public IConnection[] Connections
        {
            get
            {
                return _Connections;
            }
            private set
            {
                _Connections = value ?? throw new ArgumentNullException("Connections must not be null!");
            }
        }

        public Link()
        {
            Connections = new IConnection[0];
        }

        public Link(IConnection[] connections)
        {
            Connections = connections;
        }
    }
}
