using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.ViewModels
{
    class UserEntry
    {
        public string Username { get; set; }
        public bool IsAdmin { get; set; }
        public bool IsHighlighted { get; set; }

        public UserEntry(string username, bool isAdmin, bool isHighlighted)
        {
            Username = username;
            IsAdmin = isAdmin;
            IsHighlighted = isHighlighted;
        }
    }
}
