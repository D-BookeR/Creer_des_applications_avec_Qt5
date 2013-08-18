import QtQuick 2.0

Grid {
    columns: 2
    Label { text: "Identifiant : " }
    Input { defaultText: "entrez votre identifiant ici..." }
    Label { text: "Mot de passe : " }
    Input {
        defaultText: "entrez votre mot de passe ici..."
        defaultEchoMode: TextInput.Password
    }
}
