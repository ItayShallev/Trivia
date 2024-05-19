using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json.Serialization;
using System.Numerics;

namespace Client.Communication
{

    // ******************* REQUESTS STRUCTURES *******************
    public struct LoginRequest
    {
        [JsonPropertyName("username")] public string Username { get; set; } = "";
        [JsonPropertyName("password")] public string Password { get; set; } = "";

        public LoginRequest(string username, string password)
        {
            Username = username;
            Password = password;
        }
    }

    public struct SignupRequest
    {
        [JsonPropertyName("username")] public string Username { get; set; } = "";
        [JsonPropertyName("password")] public string Password { get; set; } = "";
        [JsonPropertyName("mail")] public string Mail { get; set; } = "";

        public SignupRequest(string username, string password, string mail)
        {
            Username = username;
            Password = password;
            Mail = mail;
        }
    }

    public struct GetPlayersInRoomRequest
    {
        [JsonPropertyName("roomID")] public uint RoomID { get; set; } = 0;

        public GetPlayersInRoomRequest(uint roomID)
        {
            RoomID = roomID;
        }
    }

    public struct JoinRoomRequest
    {
        [JsonPropertyName("roomID")] public uint RoomID { get; set; } = 0;

        public JoinRoomRequest(uint roomID)
        {
            RoomID = roomID;
        }
    }

    public struct CreateRoomRequest
    {
        [JsonPropertyName("roomName")] public string RoomName { get; set; } = "";
        [JsonPropertyName("maxPlayers")] public uint MaxPlayers { get; set; } = 0;
        [JsonPropertyName("questionCount")] public uint QuestionCount { get; set; } = 0;
        [JsonPropertyName("answerTimeout")] public uint AnswerTimeout { get; set; } = 0;

        public CreateRoomRequest(string roomName, uint maxPlayers, uint questionCount, uint answerTimeout)
        {
            RoomName = roomName;
            MaxPlayers = maxPlayers;
            QuestionCount = questionCount;
            AnswerTimeout = answerTimeout;
        }
    }


    // ******************* RESPONSE STRUCTURES *******************
    public struct ErrorResponse
    {
        [JsonPropertyName("message")] public string Message { get; set; } = "";

        public ErrorResponse(string message)
        {
            Message = message;
        }
    }

    public struct LoginResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public LoginResponse(uint status)
        {
            Status = status;
        }
    }

    public struct SignupResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public SignupResponse(uint status)
        {
            Status = status;
        }
    }

    public struct LogoutResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public LogoutResponse(uint status)
        {
            Status = status;
        }
    }

    public struct GetRoomsResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("rooms")] public List<RoomData> Rooms { get; set; } = new List<RoomData>();

        public GetRoomsResponse(uint status, List<RoomData> rooms)
        {
            Status = status;
            Rooms = rooms;
        }
    }

    public struct GetPlayersInRoomResponse
    {
        [JsonPropertyName("players")] public List<string> Players { get; set; } = new List<string>();

        public GetPlayersInRoomResponse(List<string> players)
        {
            Players = players;
        }
    }

    public struct GetHighScoreResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("statistics")] public List<string> Statistics { get; set; } = new List<string>();

        public GetHighScoreResponse(uint status, List<string> statistics)
        {
            Status = status;
            Statistics = statistics;
        }
    }

    public struct GetPersonalStatsResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("statistics")] public List<string> Statistics { get; set; } = new List<string>();

        public GetPersonalStatsResponse(uint status, List<string> statistics)
        {
            Status = status;
            Statistics = statistics;
        }
    }

    public struct JoinRoomResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public JoinRoomResponse(uint status)
        {
            Status = status;
        }
    }

    public struct CreateRoomResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public CreateRoomResponse(uint status)
        {
            Status = status;
        }
    }

    public struct RoomData
    {
        [JsonPropertyName("id")] public uint Id { get; set; } = 0;
        [JsonPropertyName("name")] public string Name { get; set; } = "";
        [JsonPropertyName("maxPlayers")] public uint MaxPlayers { get; set; } = 0;
        [JsonPropertyName("numOfQuestionsInGame")] public uint NumOfQuestionsInGame { get; set; } = 0;
        [JsonPropertyName("timePerQuestion")] public uint TimePerQuestion { get; set; } = 0;
        [JsonPropertyName("roomState")] public Constants.RoomState RoomState { get; set; } = Constants.RoomState.Waiting;

        public RoomData(uint id, string name, uint maxPlayers, uint numOfQuestionsInGame, uint timePerQuestion,
            Constants.RoomState roomState)
        {
            Id = id;
            Name = name;
            MaxPlayers = maxPlayers;
            NumOfQuestionsInGame = numOfQuestionsInGame;
            RoomState = roomState;
        }
    }
}
