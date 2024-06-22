using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json.Serialization;
using System.Numerics;
using System.Runtime.InteropServices.ComTypes;
using System.Windows.Ink;
using System.Runtime.Intrinsics;

namespace Client.Communication
{
    // ********************************************************* REQUESTS STRUCTURES *********************************************************
    public struct LogoutRequest
    {
        [JsonPropertyName("username")] public string Username { get; set; } = "";

        public LogoutRequest(string username)
        {
            Username = username;
        }
    }

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

    public struct CreateRoomRequest
    {
        [JsonPropertyName("admin")] public string Admin { get; set; } = "";
        [JsonPropertyName("roomName")] public string RoomName { get; set; } = "";
        [JsonPropertyName("maxPlayers")] public uint MaxPlayers { get; set; } = 0;
        [JsonPropertyName("questionCount")] public uint QuestionCount { get; set; } = 0;
        [JsonPropertyName("answerTimeout")] public uint AnswerTimeout { get; set; } = 0;

        public CreateRoomRequest(string admin, string roomName, uint maxPlayers, uint questionCount, uint answerTimeout)
        {
            Admin = admin;
            RoomName = roomName;
            MaxPlayers = maxPlayers;
            QuestionCount = questionCount;
            AnswerTimeout = answerTimeout;
        }
    }

    public struct GetRoomsRequest { }

    public struct GetPlayersInRoomRequest
    {
        [JsonPropertyName("roomId")] public uint RoomId { get; set; } = 0;

        public GetPlayersInRoomRequest(uint roomId)
        {
            RoomId = roomId;
        }
    }

    public struct JoinRoomRequest
    {
        [JsonPropertyName("roomId")] public uint RoomId { get; set; } = 0;

        public JoinRoomRequest(uint roomId)
        {
            RoomId = roomId;
        }
    }

    public struct GetPersonalStatisticsRequest { }

    public struct GetHighScoreRequest { }

    public struct CheckIfUserExistsRequest
    {
        [JsonPropertyName("username")] public string Username { get; set; } = "";

        public CheckIfUserExistsRequest(string username)
        {
            Username = username;
        }
    }

    public struct CloseRoomRequest
    {
        [JsonPropertyName("roomId")] public uint RoomId { get; set; } = 0;

        public CloseRoomRequest(uint roomId)
        {
            RoomId = roomId;
        }
    }

    public struct LeaveRoomRequest { }

    public struct GetRoomStateRequest
    {
        [JsonPropertyName("roomId")] public uint RoomId { get; set; } = 0;

        public GetRoomStateRequest(uint roomId)
        {
            RoomId = roomId;
        }
    }

    public struct GetQuestionRequest { }

    public struct StartGameRequest
    {
        [JsonPropertyName("roomId")] public uint RoomId { get; set; } = 0;

        public StartGameRequest(uint roomId)
        {
            RoomId = roomId;
        }
    }

    public struct SubmitAnswerRequest
    {
        [JsonPropertyName("answerId")] public uint AnswerId { get; set; } = 0;
        [JsonPropertyName("answerTime")] public double AnswerTime { get; set; } = 0.0;

        public SubmitAnswerRequest(uint answerId, double answerTime)
        {
            AnswerId = answerId;
            AnswerTime = answerTime;
        }
    }

    public struct LeaveGameRequest { }

    public struct GetGameResultsRequest { }



    // ********************************************************* RESPONSE STRUCTURES *********************************************************
    public struct LogoutResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public LogoutResponse(uint status)
        {
            Status = status;
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

    public struct CreateRoomResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 5;
        [JsonPropertyName("roomData")] public RoomData RoomData { get; set; }

        public CreateRoomResponse(uint status, RoomData roomData)
        {
            Status = status;
            RoomData = roomData;
        }
    }

    public struct GetRoomsResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("rooms")] public List<RoomData> Rooms { get; set; } = [];

        public GetRoomsResponse(uint status, List<RoomData> rooms)
        {
            Status = status;
            Rooms = rooms;
        }
    }

    public struct GetPlayersInRoomResponse
    {
        [JsonPropertyName("players")] public List<string> Players { get; set; } = [];

        public GetPlayersInRoomResponse(List<string> players)
        {
            Players = players;
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

    public struct GetPersonalStatisticsResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("statistics")] public HighScoreRow Statistics { get; set; }

        public GetPersonalStatisticsResponse(uint status, HighScoreRow statistics)
        {
            Status = status;
            Statistics = statistics;
        }
    }

    public struct GetHighScoreResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("statistics")] public List<HighScoreRow> Statistics { get; set; } = [];

        public GetHighScoreResponse(uint status, List<HighScoreRow> statistics)
        {
            Status = status;
            Statistics = statistics;
        }
    }

    public struct CheckIfUserExistsResponse
    {
        [JsonPropertyName("exists")] public bool Exists { get; set; } = true;

        public CheckIfUserExistsResponse(bool exists)
        {
            Exists = exists;
        }
    }

    public struct CloseRoomResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public CloseRoomResponse(uint status)
        {
            Status = status;
        }
    }

    public struct LeaveRoomResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public LeaveRoomResponse(uint status)
        {
            Status = status;
        }
    }

    public struct StartGameResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;

        public StartGameResponse(uint status)
        {
            Status = status;
        }
    }

    public struct GetRoomStateResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 1;
        [JsonPropertyName("hasGameBegan")] public bool HasGameBegan { get; set; } = false;
        [JsonPropertyName("players")] public List<string> Players { get; set; } = new List<string>();
        [JsonPropertyName("questionCount")] public uint QuestionCount { get; set; } = 0;
        [JsonPropertyName("answerTimeout")] public uint AnswerTimeout { get; set; } = 0;
        [JsonPropertyName("roomStatus")] public Constants.RoomStatus RoomStatus { get; set; } = 0;

        public GetRoomStateResponse(uint status, bool hasGameBegan, List<string> players, uint questionCount, uint answerTimeout, Constants.RoomStatus roomStatus)
        {
            Status = status;
            HasGameBegan = hasGameBegan;
            Players = players;
            QuestionCount = questionCount;
            AnswerTimeout = answerTimeout;
            RoomStatus = roomStatus;
        }
    }

    public struct GetQuestionResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 0;
        [JsonPropertyName("question")] public List<int> Question { get; set; } = [];
        [JsonPropertyName("answers")] public List<AnswerItem> Answers { get; set; } = [];
        [JsonPropertyName("difficulty")] public Constants.QuestionDifficulty Difficulty { get; set; }

        public GetQuestionResponse(uint status, List<int> question, List<AnswerItem> answers, Constants.QuestionDifficulty questionDifficulty)
        {
            Status = status;
            Question = question;
            Answers = answers;
            Difficulty = questionDifficulty;
        }
    }

    public struct SubmitAnswerResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 0;
        [JsonPropertyName("correctAnswerId")] public uint CorrectAnswerId { get; set; } = 0;

        public SubmitAnswerResponse(uint status, uint correctAnswerId)
        {
            Status = status;
            CorrectAnswerId = correctAnswerId;
        }
    }
    
    public struct LeaveGameResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 0;

        public LeaveGameResponse(uint status)
        {
            Status = status;
        }
    }

    public struct GetGameResultsResponse
    {
        [JsonPropertyName("status")] public uint Status { get; set; } = 0;
        [JsonPropertyName("playerResults")] public List<PlayerResults> Results { get; set; }

        public GetGameResultsResponse(uint status, List<PlayerResults> results)
        {
            Status = status;
            Results = results;
        }
    }

    public struct ErrorResponse
    {
        [JsonPropertyName("message")] public string Message { get; set; } = "";

        public ErrorResponse(string message)
        {
            Message = message;
        }
    }



    // ********************************************************* OTHERS *********************************************************
    public struct RoomData
    {
        [JsonPropertyName("id")] public uint Id { get; set; } = 0;
        [JsonPropertyName("name")] public string Name { get; set; } = "";
        [JsonPropertyName("admin")] public string Admin { get; set; } = "";
        [JsonPropertyName("maxPlayers")] public uint MaxPlayers { get; set; } = 0;
        [JsonPropertyName("numOfQuestionsInGame")] public uint NumOfQuestionsInGame { get; set; } = 0;
        [JsonPropertyName("timePerQuestion")] public uint TimePerQuestion { get; set; } = 0;
        [JsonPropertyName("roomStatus")] public Constants.RoomStatus RoomStatus { get; set; } = Constants.RoomStatus.Playing;

        public RoomData(uint id, string name, string admin, uint maxPlayers, uint numOfQuestionsInGame, uint timePerQuestion,
            Constants.RoomStatus roomStatus)
        {
            Id = id;
            Name = name;
            Admin = admin;
            MaxPlayers = maxPlayers;
            NumOfQuestionsInGame = numOfQuestionsInGame;
            RoomStatus = roomStatus;
        }
    }

    public struct ResponseInfo
    {
        public string ResponseId { get; set; }
        public int MessageLength { get; set; }
        public string Message { get; set; }
    }


    public struct AnswerItem
    {
        [JsonPropertyName("answerId")] public uint AnswerId { get; set; } = 0;
        [JsonPropertyName("answer")] public List<int> Answer { get; set; } = [];

        public AnswerItem(uint answerId, List<int> answer)
        {
            AnswerId = answerId;
            Answer = answer;
        }
    }

    public struct HighScoreRow
    {
        [JsonPropertyName("username")] public string Username { get; set; } = "";
        [JsonPropertyName("numGamesPlayed")] public uint NumGamesPlayed { get; set; } = 0;
        [JsonPropertyName("numCorrectAnswers")] public uint NumCorrectAnswers { get; set; } = 0;
        [JsonPropertyName("numWrongAnswers")] public uint NumWrongAnswers { get; set; } = 0;
        [JsonPropertyName("averageAnswerTime")] public double AverageAnswerTime { get; set; } = 0.0;
        [JsonPropertyName("points")] public uint Points { get; set; } = 0;
        [JsonPropertyName("rank")] public uint Rank { get; set; } = 0;

        public HighScoreRow(string username, uint numGamesPlayed, uint numCorrectAnswers, uint numWrongAnswers, double averageAnswerTime, uint points, uint rank)
        {
            Username = username;
            NumGamesPlayed = numGamesPlayed;
            NumCorrectAnswers = numCorrectAnswers;
            NumWrongAnswers = numWrongAnswers;
            AverageAnswerTime = averageAnswerTime;
            Points = points;
            Rank = rank;
        }
    }

    public struct PlayerResults
    {
        [JsonPropertyName("username")] public string Username { get; set; }
        [JsonPropertyName("correctAnswerCount")] public uint CorrectAnswerCount { get; set; }
        [JsonPropertyName("wrongAnswerCount")] public uint WrongAnswerCount { get; set; }
        [JsonPropertyName("averageAnswerTime")] public double AverageAnswerTime { get; set; }
        [JsonPropertyName("points")] public uint Points { get; set; }
        [JsonPropertyName("rank")] public uint Rank { get; set; }


        public PlayerResults(string username, uint correctAnswerCount, uint wrongAnswerCount, double averageAnswerTime, uint points, uint rank)
        {
            Username = username;
            CorrectAnswerCount = correctAnswerCount;
            WrongAnswerCount = wrongAnswerCount;
            AverageAnswerTime = averageAnswerTime;
            Points = points;
            Rank = rank;
        }
    };
}
