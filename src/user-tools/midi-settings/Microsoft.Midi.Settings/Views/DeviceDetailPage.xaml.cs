using Microsoft.Midi.Settings.ViewModels;
using Microsoft.Midi.Settings;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Popups;
using Microsoft.UI.Windowing;
using Windows.Storage.Pickers;
using WinRT.Interop;
using Microsoft.Midi.Settings.ViewModels.Data;
using Microsoft.UI.Xaml.Media.Imaging;
using Windows.Storage.Streams;
using Windows.Storage;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace Microsoft.Midi.Settings.Views
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DeviceDetailPage : Page
    {
        public DeviceDetailViewModel ViewModel
        {
            get;
        }


        public DeviceDetailPage()
        {
            ViewModel = App.GetService<DeviceDetailViewModel>();

            this.InitializeComponent();
        }

 
        private async void Button_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.UserMetadata.Name = ViewModel.DeviceInformation.UserSuppliedName;
            ViewModel.UserMetadata.Description = ViewModel.DeviceInformation.UserSuppliedDescription;
            ViewModel.UserMetadata.LargeImagePath = ViewModel.DeviceInformation.UserSuppliedLargeImagePath;
            ViewModel.UserMetadata.SmallImagePath = ViewModel.DeviceInformation.UserSuppliedSmallImagePath;

            editUserDefinedPropertiesDialog.Width = this.Width / 3;


            // TODO: Should probably have these in the viewmodel as
            // we'll need a renderable image anyway. This code is temp

            if (ViewModel.UserMetadata.LargeImagePath != string.Empty)
            {
                var file = await StorageFile.GetFileFromPathAsync(ViewModel.UserMetadata.LargeImagePath);

                if (file != null)
                {
                    // Open a stream for the selected file.
                    // The 'using' block ensures the stream is disposed
                    // after the image is loaded.
                    using (IRandomAccessStream fileStream =
                        await file.OpenAsync(FileAccessMode.Read))
                    {
                        // Set the image source to the selected bitmap.
                        var bitmapImage = new BitmapImage();

                        bitmapImage.SetSource(fileStream);

                        UserMetadataLargeImagePreview.Source = bitmapImage;
                    }
                }
            }

            if (ViewModel.UserMetadata.SmallImagePath != string.Empty)
            {
                var file = await StorageFile.GetFileFromPathAsync(ViewModel.UserMetadata.SmallImagePath);

                if (file != null)
                {
                    // Open a stream for the selected file.
                    // The 'using' block ensures the stream is disposed
                    // after the image is loaded.
                    using (IRandomAccessStream fileStream =
                        await file.OpenAsync(FileAccessMode.Read))
                    {
                        // Set the image source to the selected bitmap.
                        var bitmapImage = new BitmapImage();

                        bitmapImage.SetSource(fileStream);

                        UserMetadataSmallImagePreview.Source = bitmapImage;
                    }
                }
            }



            ContentDialogResult result = await editUserDefinedPropertiesDialog.ShowAsync(ContentDialogPlacement.Popup);

            if (result == ContentDialogResult.Primary)
            {
                // save the changes


                // refresh the device information?

            }
        }

        // edit popup
        private async void BrowseLargeImage_Click(object sender, RoutedEventArgs e)
        {
            var filePicker = App.MainWindow.CreateOpenFilePicker();

            filePicker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            filePicker.FileTypeFilter.Add(".png");
            filePicker.FileTypeFilter.Add(".jpg");
            filePicker.FileTypeFilter.Add(".svg");

            var file = await filePicker.PickSingleFileAsync();

            if (file != null)
            {
                // update the edit vm
                ViewModel.UserMetadata.LargeImagePath = file.Path;

                // Open a stream for the selected file.
                // The 'using' block ensures the stream is disposed
                // after the image is loaded.
                using (IRandomAccessStream fileStream =
                    await file.OpenAsync(FileAccessMode.Read))
                {
                    // Set the image source to the selected bitmap.
                    var bitmapImage = new BitmapImage();

                    bitmapImage.SetSource(fileStream);

                    UserMetadataLargeImagePreview.Source = bitmapImage;
                }

            }
        }

        // edit popup
        private async void BrowseSmallImage_Click(object sender, RoutedEventArgs e)
        {
            var filePicker = App.MainWindow.CreateOpenFilePicker();

            filePicker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            filePicker.FileTypeFilter.Add(".png");
            filePicker.FileTypeFilter.Add(".jpg");
            filePicker.FileTypeFilter.Add(".svg");

            var file = await filePicker.PickSingleFileAsync();

            if (file != null)
            {
                // update the edit vm
                ViewModel.UserMetadata.SmallImagePath = file.Path;

                // Open a stream for the selected file.
                // The 'using' block ensures the stream is disposed
                // after the image is loaded.
                using (IRandomAccessStream fileStream =
                    await file.OpenAsync(FileAccessMode.Read))
                {
                    // Set the image source to the selected bitmap.
                    var bitmapImage = new BitmapImage();

                    bitmapImage.SetSource(fileStream);

                    UserMetadataSmallImagePreview.Source = bitmapImage;
                }
            }

        }
    }
}
