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
                new Link(),
                new Link()
            };

            List<Component> components = new List<Component>
            {
                new Components.CLK(new Link[] { links[3] }, new Link[] { links[0] }, 0, 16)
                
            };

            for(int i = 0; i < 1000; i++)
            {
                components.Add(new Components.AND(new Link[] { links[0], links[1] }, new Link[] { links[2] }, i + 1));
            }

            Board.Init(components.ToArray());

            Board.Start();
        }
    }
}
