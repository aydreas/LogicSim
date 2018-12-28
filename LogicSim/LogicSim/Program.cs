using System;
using System.Collections.Generic;

namespace LogicSim
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Component> components = new List<Component>();
            List<Link> links = new List<Link>();

            Board.Init(new Component[0]);
        }
    }
}
