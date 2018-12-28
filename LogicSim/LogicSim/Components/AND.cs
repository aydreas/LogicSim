using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim.Components
{
    class AND : Component
    {
        public override int InputCount => 2;
        public override int OutputCount => 1;

        public override void Compute()
        {
            Outputs[0].Powered = Inputs[0].Powered && Inputs[1].Powered;
        }

        public AND(Input[] inputs, Output[] outputs, int index) : base(inputs, outputs, index) { }
        public AND(Link[] inputs, Link[] outputs, int index) : base(inputs, outputs, index) { }
    }
}
