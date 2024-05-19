using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public static class Constants
    {
        public enum RoomState
        {
            Waiting = 0,
            Playing = 1,
            Finished = 2 // future use?
        };
    }
}
