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

        public UserEntry(string username, bool isAdmin)
        {
            Username = username;
            IsAdmin = isAdmin;
        }
    }
}
