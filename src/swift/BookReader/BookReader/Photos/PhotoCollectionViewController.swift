/// Copyright (c) 2018 Razeware LLC
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// Notwithstanding the foregoing, you may not use, copy, modify, merge, publish,
/// distribute, sublicense, create a derivative work, and/or sell copies of the
/// Software in any work that is designed, intended, or marketed for pedagogical or
/// instructional purposes related to programming, coding, application development,
/// or information technology.  Permission for such use, copying, modification,
/// merger, publication, distribution, sublicensing, creation of derivative works,
/// or sale is expressly withheld.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.

/// Copyright (c) 2018 Razeware LLC
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// Notwithstanding the foregoing, you may not use, copy, modify, merge, publish,
/// distribute, sublicense, create a derivative work, and/or sell copies of the
/// Software in any work that is designed, intended, or marketed for pedagogical or
/// instructional purposes related to programming, coding, application development,
/// or information technology.  Permission for such use, copying, modification,
/// merger, publication, distribution, sublicensing, creation of derivative works,
/// or sale is expressly withheld.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.


//TODO: Get rid of internet option. replace with camera option
import UIKit
import Photos

private let reuseIdentifier = "photoCell"
private let backgroundImageOpacity: CGFloat = 0.1

final class PhotoCollectionViewController: UICollectionViewController {
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //main thread starts here
        
        /////////////////////////////
        //set the background, and have it be slightly transparent and in the center
        let backgroundImageView = UIImageView(image: UIImage(named:"background"))
        backgroundImageView.alpha = backgroundImageOpacity
        backgroundImageView.contentMode = .center
        collectionView?.backgroundView = backgroundImageView
        ////////////////////////////
        
        ////////////////////////////
        //Add entry for the notification center dispatch table
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(contentChangedNotification(_:)),
            name: PhotoManagerNotification.contentUpdated,
            object: nil)
        //Add entry for the notification center dispatch table
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(contentChangedNotification(_:)),
            name: PhotoManagerNotification.contentAdded,
            object: nil)
        ////////////////////////////
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        showOrHideNavPrompt()
    }
    
    // MARK: - IBAction Methods
    @IBAction private func addPhotoAssets(_ sender: Any) {
        //The whole block of code here is creating the notification table
        
        
        ////////////////////////////
        //This is the title for the notification dispatch table...creates the table "controller"
        //action sheet is the table instead of the alert
        let alert = UIAlertController(title: "Get Photos From:", message: nil, preferredStyle: .actionSheet)
        
        //this is the cancel button on the dispatch table
        //addaction adds a button to the table
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        alert.addAction(cancelAction)
        ////////////////////////////
        
        ////////////////////////////
        //create action for accessing the photo library
        let libraryAction = UIAlertAction(title: "Photo Library", style: .default) { _ in
            let viewController = self.storyboard?.instantiateViewController(withIdentifier: "AlbumsStoryboard") as? UINavigationController
            //The action is that it formats the pictures in the library, and then displays them
            if let viewController = viewController,
                let albumsTableViewController = viewController.topViewController as? AlbumsTableViewController {
                albumsTableViewController.assetPickerDelegate = self
                self.present(viewController, animated: true, completion: nil)
            }
        }
        alert.addAction(libraryAction)
        ////////////////////////////
        
        ////////////////////////////
        //Add action for accessing the internet
        let internetAction = UIAlertAction(title: "Le Internet", style: .default) { _ in
            self.downloadImageAssets()
        }
        alert.addAction(internetAction)
        ////////////////////////////
        
        present(alert, animated: true, completion: nil)
    }
}

// MARK: - Private Methods
//This stuff wont be implemented
private extension PhotoCollectionViewController {
    func showOrHideNavPrompt() {
        // Implement me!
    }
    
    func downloadImageAssets() {
        PhotoManager.shared.downloadPhotos() { [weak self] error in
            let message = error?.localizedDescription ?? "The images have finished downloading"
            let alert = UIAlertController(title: "Download Complete", message: message, preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: nil))
            self?.present(alert, animated: true, completion: nil)
        }
    }
}

// MARK: - Notification handlers
extension PhotoCollectionViewController {
    @objc func contentChangedNotification(_ notification: Notification!) {
        collectionView?.reloadData()
        showOrHideNavPrompt()
    }
}

// MARK: - UICollectionViewDataSource
extension PhotoCollectionViewController {
    override func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return PhotoManager.shared.photos.count
    }
    
    override func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: reuseIdentifier, for: indexPath) as! PhotoCollectionViewCell
        
        let photoAssets = PhotoManager.shared.photos
        let photo = photoAssets[indexPath.row]
        
        switch photo.statusThumbnail {
        case .goodToGo:
            cell.thumbnailImage = photo.thumbnail
        case .downloading:
            cell.thumbnailImage = UIImage(named: "photoDownloading")
        case .failed:
            cell.thumbnailImage = UIImage(named: "photoDownloadError")
        }
        
        return cell
    }
}

// MARK: - UICollectionViewDelegate
extension PhotoCollectionViewController {
    override func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        let photos = PhotoManager.shared.photos
        let photo = photos[indexPath.row]
        
        switch photo.statusImage {
        case .goodToGo:
            let viewController = storyboard?.instantiateViewController(withIdentifier: "PhotoDetailStoryboard") as? PhotoDetailViewController
            if let viewController = viewController {
                viewController.image = photo.image
                navigationController?.pushViewController(viewController, animated: true)
            }
            
        case .downloading:
            let alert = UIAlertController(title: "Downloading",
                                          message: "The image is currently downloading",
                                          preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: nil))
            present(alert, animated: true, completion: nil)
            
        case .failed:
            let alert = UIAlertController(title: "Image Failed",
                                          message: "The image failed to be created",
                                          preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: nil))
            present(alert, animated: true, completion: nil)
        }
    }
}

// MARK: - AssetPickerDelegate

extension PhotoCollectionViewController: AssetPickerDelegate {
    func assetPickerDidCancel() {
        dismiss(animated: true, completion: nil)
    }
    
    func assetPickerDidFinishPickingAssets(_ selectedAssets: [PHAsset])  {
        for asset in selectedAssets {
            let photo = AssetPhoto(asset: asset)
            PhotoManager.shared.addPhoto(photo)
        }
        
        dismiss(animated: true, completion: nil)
    }
}


/*
import UIKit
import Photos

private let reuseIdentifier = "photoCell"
private let backgroundImageOpacity: CGFloat = 0.1

final class PhotoCollectionViewController: UICollectionViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UICollectionViewDelegateFlowLayout {
    
  // MARK: - Lifecycle
  override func viewDidLoad() {
    super.viewDidLoad()
    
    //main thread starts here
    
    /////////////////////////////
    //set the background, and have it be slightly transparent and in the center
    let backgroundImageView = UIImageView(image: UIImage(named:"background"))
    backgroundImageView.alpha = backgroundImageOpacity
    backgroundImageView.contentMode = .center
    collectionView?.backgroundView = backgroundImageView
    ////////////////////////////
    
    ////////////////////////////
    //Add entry for the notification center dispatch table
    NotificationCenter.default.addObserver(
      self,
      selector: #selector(contentChangedNotification(_:)),
      name: PhotoManagerNotification.contentUpdated,
      object: nil)
    //Add entry for the notification center dispatch table
    NotificationCenter.default.addObserver(
      self,
      selector: #selector(contentChangedNotification(_:)),
      name: PhotoManagerNotification.contentAdded,
      object: nil)
    ////////////////////////////
  }
  
  override func viewDidAppear(_ animated: Bool) {
    super.viewDidAppear(animated)
    //showOrHideNavPrompt()
  }
  
  // MARK: - IBAction Methods
  @IBAction private func addPhotoAssets(_ sender: Any) {
    //The whole block of code here is creating the notification table
    
    
    ////////////////////////////
    //This is the title for the notification dispatch table...creates the table "controller"
    //action sheet is the table instead of the alert
    let alert = UIAlertController(title: "Get Photos From:", message: nil, preferredStyle: .actionSheet)
    
    //this is the cancel button on the dispatch table
    //addaction adds a button to the table
    let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
    alert.addAction(cancelAction)
    ////////////////////////////
    
    ////////////////////////////
    //create action for accessing the photo library
    let libraryAction = UIAlertAction(title: "Photo Library", style: .default) { _ in
      let viewController = self.storyboard?.instantiateViewController(withIdentifier: "AlbumsStoryboard") as? UINavigationController
        //The action is that it formats the pictures in the library, and then displays them
      if let viewController = viewController,
        let albumsTableViewController = viewController.topViewController as? AlbumsTableViewController {
        albumsTableViewController.assetPickerDelegate = self
        self.present(viewController, animated: true, completion: nil)
      }
    }
    alert.addAction(libraryAction)
    ////////////////////////////
    
    ////////////////////////////
    //Add action for accessing the internet
    let internetAction = UIAlertAction(title: "Le Internet", style: .default) { _ in
      //self.downloadImageAssets()
    }
    alert.addAction(internetAction)
    ////////////////////////////
    
    present(alert, animated: true, completion: nil)
  }
}

// MARK: - Notification handlers
extension PhotoCollectionViewController {
  @objc func contentChangedNotification(_ notification: Notification!) {
    collectionView?.reloadData()
    showOrHideNavPrompt()
  }
}

// MARK: - AssetPickerDelegate

extension PhotoCollectionViewController: AssetPickerDelegate {
  func assetPickerDidCancel() {
    dismiss(animated: true, completion: nil)
  }
  
  func assetPickerDidFinishPickingAssets(_ selectedAssets: [PHAsset])  {
    for asset in selectedAssets {
      let photo = AssetPhoto(asset: asset)
      PhotoManager.shared.addPhoto(photo)
    }
    
    dismiss(animated: true, completion: nil)
  }
}

// Helper function inserted by Swift 4.2 migrator.
fileprivate func convertFromUIImagePickerControllerInfoKeyDictionary(_ input: [UIImagePickerController.InfoKey: Any]) -> [String: Any] {
    return Dictionary(uniqueKeysWithValues: input.map {key, value in (key.rawValue, value)})
}

// Helper function inserted by Swift 4.2 migrator.
fileprivate func convertFromUIImagePickerControllerInfoKey(_ input: UIImagePickerController.InfoKey) -> String {
    return input.rawValue
}

*/
