using System;
using System.Collections.Generic;

namespace LogicSim
{
    class Program
    {
        static void Main(string[] args)
        {
            //creating some links to connect the components to
            List<Link> links = new List<Link>
            {
                new Link(),
                new Link(),
                new Link(),
                new Link()
            };

            /* 
             * creating a clock object and connecting it to some links
             * setting index to 0, as its our first component
             * setting speed to 16, so the clock will change its state every 16 cycles
             */
            List<Component> components = new List<Component>
            {
                new Components.CLK(new Link[] { links[3] }, new Link[] { links[0] }, 0, 16)
                
            };

            /*
             * creating some components and connecting it to the clock on the same link
             * with ascending and unique index, which is mandatory, so the simulator works correctly
             */
            for(int i = 0; i < 1000; i++)
            {
                components.Add(new Components.AND(new Link[] { links[0], links[1] }, new Link[] { links[2] }, i + 1));
            }

            //initialize board with generated components
            Board.Init(components.ToArray());

            //start the simulation
            Board.Start();
        }
    }
}
