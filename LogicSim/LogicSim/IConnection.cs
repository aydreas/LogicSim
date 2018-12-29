using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim
{
    interface IConnection
    {
        /// <summary>
        /// whether connection is powered.
        /// </summary>
        bool Powered
        {
            get;
        }

        /// <summary>
        /// Component connected to the connection.
        /// </summary>
        Component Component
        {
            get;
        }

        /// <summary>
        /// Link associated to the connection.
        /// </summary>
        Link Link
        {
            get;
        }
    }
}
