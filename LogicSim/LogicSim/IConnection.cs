using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    interface IConnection
    {
        bool Powered
        {
            get;
        }

        Component Component
        {
            get;
        }

        Link Link
        {
            get;
        }
    }
}
