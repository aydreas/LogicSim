using System;
using System.Collections.Generic;

namespace LogicSim
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Link> links = new List<Link>
            {
                new Link(),
                new Link(),
                new Link()
            };

            List<Component> components = new List<Component>
            {
                new Components.AND(new Link[] { links[0], links[1] }, new Link[] { links[2] }, 0)
            };

            Board.Init(new Component[0]);

            Board.Start();
        }
    }
}
