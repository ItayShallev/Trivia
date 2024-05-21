using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Client.Communication;

namespace Client.Pages
{
    /// <summary>
    /// Interaction logic for MenuPage.xaml
    /// </summary>
    public partial class MenuPage : Page
    {
        private string _username;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public MenuPage(string username)
        {
            InitializeComponent();
            _username = username;

            UserGreetingTextBlock.Text = "Welcome " + this._username + "!";
        }

        private void BtnPersonalStats_Click(object sender, RoutedEventArgs e)
        {
            // Redirect user to the personal stats page...
        }

        private void BtnLeaderboard_Click(object sender, RoutedEventArgs e)
        {
            // Redirect user to the leaderboard page...
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            // Redirect user to the create room page...
        }
    }
}
