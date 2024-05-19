using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public static class Constants
    {
        // ************************** SERVER CONSTANTS *************************
        public const string SERVER_IP = "127.0.0.1";
        public const int SERVER_PORT = 8888;

        // ************************** COMMUNICATION PROTOCOL CONSTANTS *************************
        public const int NUM_ZEROS_TO_PAD = 4;

        public enum RoomState
        {
            Waiting = 0,
            Playing = 1,
            Finished = 2 // future use?
        };

        // ************************** REQUEST & RESPONSE ID'S *************************
        public const int LogoutRequestId = 0;
        public const int LoginRequestId = 1;
        public const int SignupRequestId = 2;
        public const int MenuRequestId = 3;
        public const int CreateRoomRequestId = 4;
        public const int GetRoomRequestId = 5;
        public const int GetPlayersInRoomRequestId = 6;
        public const int JoinRoomRequestId = 7;
        public const int GetStatisticsRequestId = 8;
        public const int GetHighScoreRequestId = 9;

        public const int LogoutResponseId = 0;
        public const int LoginResponseId = 1;
        public const int SignupResponseId = 2;
        public const int ErrorResponseId = 3;
        public const int GetRoomsResponseId = 4;
        public const int GetPlayersInRoomResponseId = 5;
        public const int GetHighScoreResponseId = 6;
        public const int GetPersonalStatsResponseId = 7;
        public const int JoinRoomResponseId = 8;
        public const int CreateRoomResponseId = 9;
    }
}
