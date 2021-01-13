/***************************************************************************
**
** TinGen - Index Generator for Tinfoil
** Copyright (C) 2021 eXhumer
**
** $QT_BEGIN_LICENSE:GPL3$
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License
** version 3. The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL3 included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License requirements will be met:
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
**
** $QT_END_LICENSE$
**
***************************************************************************/

#include "AppWidgets/mainwindow.h"
#include "app_config.h"
#include <QCommandLineParser>
#include <QStandardPaths>
#include <QApplication>
#include <QTranslator>
#include <QDir>

int main(int argc, char *argv[])
{
    // Main application setup. Always required to do first.
    QApplication app(argc, argv);
    app.setApplicationName(PROJECT_NAME);
    app.setApplicationVersion(PROJECT_VERSION);

    // Install translator to application if found
    QTranslator appTranslator;
    if(appTranslator.load(QLocale(), PROJECT_NAME, ".", QString(), ".qm"))
        app.installTranslator(&appTranslator);

    // Add commandline parser
    QCommandLineParser parser;
    parser.setApplicationDescription(app.translate("main", "command_line.description"));
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("folder_ids", "Folder IDs of Google Drive folders to scan", "[folder_ids...]");
    parser.addOption({"app-data-path", app.translate("main", "command_line.app_data_path_description"), "app_data_path", QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)});
    parser.addOption({{"c", "credentials"}, "Path to Google Application Credentials", "credentials path", "default_path"});
    parser.addOption({{"t", "token"}, "Path to Google OAuth2.0 User Token", "token path", "default_path"});
    parser.addOption({{"i", "index"}, "Path to output index file", "index path", "default_path"});
    parser.addOption({"share-files", "Share all files inside the index file"});
    parser.addOption({"no-recursion", "Scans for files only in top directory for each Folder ID entered"});
    parser.addOption({"add-nsw-files-without-title-id", "Adds files without valid Title ID"});
    parser.addOption({"add-non-nsw-files", "Adds files without valid NSW ROM extension(NSP/NSZ/XCI/XCZ) to index"});
    parser.addOption({{"s", "success"}, "Adds a success message to index file to show if index is successfully read by Tinfoil", "val"});
    parser.addOption({{"e", "encrypt"}, "Encrypts the resulting index file with AES-ECB-256"});
    parser.addOption({"public-key", "Path to RSA Public Key to encrypt AES-ECB-256 key with", "rsa public key path", "def"});
    //parser.addOption(encryptVMPathOption);
    parser.addOption({"upload-to-folder-id", "Upload resulting index to Folder ID supplied", "upload folder id"});
    parser.addOption({"upload-to-my-drive", "Upload resulting index to My Drive"});
    parser.addOption({"new-upload-id", "Uploads the newly generated index file with a new File ID instead of"});
    parser.addOption({"share-uploaded-index", "Shares the index file that is uploaded to Google Drive"});
    parser.addOption({{"zstandard", "zstd"}, "Compresses index with zstandard compression method"});
    parser.addOption({"zlib", "Compresses index with zlib compression method"});
    parser.addOption({"no-compress", "Flag to not compress index"});
    parser.process(app);
    QString appDataPath = parser.value("app-data-path");
    QDir appDataDir(appDataPath);

    // Create appdata folder if it doesn't exist
    if(!appDataDir.exists())
        appDataDir.mkpath(".");

    MainWindow win;
    win.show();
    return app.exec();
}
