using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Client.Communication;

namespace Client.ViewModels
{
    internal class RoomEntry
    {
        public string Name { get; set; }
        public string Admin { get; set; }
        public string State { get; set; }
        public uint QuestionCount { get; set; }
        public uint QuestionTimeout { get; set; }
        public RoomData RoomData { get; set; }

        public RoomEntry(string name, string admin, string state, uint questionCount, uint questionTimeout, RoomData roomData)
        {
            Name = name;
            Admin = admin;
            State = state;
            QuestionCount = questionCount;
            QuestionTimeout = questionTimeout;
            RoomData = roomData;
        }
    }
}
