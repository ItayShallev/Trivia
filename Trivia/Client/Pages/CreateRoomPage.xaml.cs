using MaterialDesignThemes.Wpf;
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
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        private string _username;

        public string Username
        {
            get { return _username; }
            set { _username = value; }
        }

        public CreateRoomPage(string username)
        {
            InitializeComponent();

            Username = username;

            // Focusing on the room name text box
            RoomNameTextBox.Focus();
        }
        
        private void RoomNameTextBox_OnTextChanged(object sender, RoutedEventArgs e)
        {
            if (BtnCreateRoom != null)
            {
                BtnCreateRoom.IsEnabled = ((RoomNameTextBox.Text != "") && (MaxPlayersComboBox.Text != "Select number of players"));
            }
        }

        private void MaxPlayersComboBox_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (BtnCreateRoom != null)
            {
                ComboBoxItem selectedItem = MaxPlayersComboBox.SelectedItem as ComboBoxItem;
                string selectedValue = selectedItem?.Content.ToString();

                BtnCreateRoom.IsEnabled = ((RoomNameTextBox.Text != "") && (selectedValue != "Select number of players"));
            }
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            // Sending a create room request to the server
            CreateRoomRequest createRoomRequest = new CreateRoomRequest(Username, RoomNameTextBox.Text,
                uint.Parse(MaxPlayersComboBox.Text), uint.Parse(QuestionCountLabel.Content.ToString()), uint.Parse(TimePerQuestionLabel.Content.ToString()));
            Helper.SendRequest(Constants.CreateRoomRequestId, JsonSerializer.Serialize(createRoomRequest));

            CreateRoomResponse createRoomResponse = Helper.GetResponse<CreateRoomResponse>();       // Getting the server's response

            // Checking if the server has approved to create the room
            if (createRoomResponse.Status == 1)
            {
                // Navigating the user to the waiting room
                AdminWaitingRoomPage adminWaitingRoomPage = new AdminWaitingRoomPage(createRoomResponse.RoomData, Username);
                NavigationService.Navigate(adminWaitingRoomPage);
            }
        }

        private void GoBackArrow_OnGoBackClicked(object sender, RoutedEventArgs e)
        {
            NavigationService.GoBack();
        }
    }
}
