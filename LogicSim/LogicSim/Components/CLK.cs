using System;
using System.Collections.Generic;
using System.Text;

namespace LogicSim.Components
{
    class CLK : Component
    {
        public override int InputCount => 1;
        public override int OutputCount => 1;

        private bool Subscribed = false;
        private int Speed = 1;
        private int TickCount = 0;

        public CLK(Input[] inputs, Output[] outputs, int index) : base(inputs, outputs, index)
        {
            ActivateDeactivate();
        }
        public CLK(Link[] inputs, Link[] outputs, int index) : base(inputs, outputs, index)
        {
            ActivateDeactivate();
        }

        public CLK(Input[] inputs, Output[] outputs, int index, int speed) : base(inputs, outputs, index)
        {
            Speed = speed;
            ActivateDeactivate();
        }

        public CLK(Link[] inputs, Link[] outputs, int index, int speed) : base(inputs, outputs, index)
        {
            Speed = speed;
            ActivateDeactivate();
        }

        public override void Compute()
        {
            ActivateDeactivate();
        }

        private void ActivateDeactivate()
        {
            if (Inputs[0].Powered)
            {
                if (Subscribed)
                {
                    Board.TickEvent -= Tick;
                    Subscribed = false;
                }
            }
            else
            {
                if (!Subscribed)
                {
                    Board.TickEvent += Tick;
                    Subscribed = true;
                }
            }
        }

        private void Tick(object sender, EventArgs e)
        {
            TickCount++;

            if (TickCount >= Speed)
            {
                if (Outputs[0].Powered)
                    Outputs[0].Powered = false;
                else
                    Outputs[0].Powered = true;

                TickCount = 0;
            }
        }
    }
}
