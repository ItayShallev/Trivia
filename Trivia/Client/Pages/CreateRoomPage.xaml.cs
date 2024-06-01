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
        public CreateRoomPage()
        {
            InitializeComponent();
        }

        private void UIElement_OnMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            NavigationService.GoBack();
        }

        // Checks if the rooms settings are valid and ready for "CreateRoom" Request
        private bool AreRoomSettingsValid()
        {
            return (MaxPlayersComboBox.Text != "Select number of players") && (RoomNameTextBox.Text != "");
        }

        private void BtnCreateRoom_Click(object sender, RoutedEventArgs e)
        {
            if (AreRoomSettingsValid())
            {
                // Sending a create room request to the server
                CreateRoomRequest createRoomRequest = new CreateRoomRequest(RoomNameTextBox.Text,
                    uint.Parse(MaxPlayersComboBox.Text), 20, uint.Parse(QuetionTimoutLable.Content.ToString()));
                Helper.SendRequest(Constants.CreateRoomRequestId, JsonSerializer.Serialize(createRoomRequest));

                CreateRoomResponse createRoomResponse = Helper.GetResponse<CreateRoomResponse>();       // Getting the server's response

                // Checking if the server has approved to create the room
                if (createRoomResponse.Status == 1)
                {
                    // Navigating the user to the waiting room
                    WaitingRoomPage waitingRoomPage = new WaitingRoomPage(createRoomResponse.RoomData);
                    NavigationService.Navigate(waitingRoomPage);
                }
            }
        }
    }
}
