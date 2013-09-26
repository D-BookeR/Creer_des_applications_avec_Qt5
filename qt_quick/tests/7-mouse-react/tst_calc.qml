import QtQuick 2.0
import QtTest 1.0
import "Calculator.js" as Calculator

Item {
    width: root.width
    height: root.height

    Main {
        id: root
    }

    TestCase {
        name: "Calculator.js"

        function test_evalToUser_data() {
            return [{ input: "1+2", expected: "1+2" }, // No change
                    { input: "1-2", expected: "1–2" }, // ASCII - vs &#0150;
                    { input: "1*2", expected: "1×2" }, // * vs ×
                    { input: "1/2", expected: "1÷2" }] // / vs ÷
        }

        function test_evalToUser(data) {
            compare(Calculator.evalToUser(data.input), data.expected)
        }
    }

    TestCase {
        name: "gui"
        when: windowShown

        function init() {
            root.children[0].model.clear()
        }

        function init_data() {
            return [{ sequence: ['1', '+', '2'], result: 3 },
                    { sequence: ['3', '*', '4', '-', '5'], result: 7 },
                    { sequence: ['9', '/', '6'], result: 1.5},
                    { sequence: ['-', '8', '+', '7'], result: -1}]
        }

        function test_keyboard(data) {
            data.sequence.map(keyClick)
            keyClick(Qt.Key_Return)
            compare_result(data.result)
        }

        function test_mouse(data) {
            var face = root.children[1];
            var numpad = face.children[0];
            var oppad = face.children[1];

            // Exécuter la séquence d'opérations. 
            data.sequence.map(function(key) {
                // Trouver le bouton. 
                var button = find_button(numpad, key)
                if(button === false)
                    button = find_button(oppad, key)
                if(button === false)
                    // Erreur : le bouton n'existe pas sur les claviers 
                    // (n'est possible que si les tests sont incorrects). 
                    console.log('!42!')

                // Le cliquer. 
                mouseClick(button, button.width / 2, button.height / 2)
            })

            // Dernière étape : appuyer sur =.
            var button = find_button(numpad, "=")
            mouseClick(button, button.width / 2, button.height / 2)

            // Finalement, vérifier le résultat. 
            compare_result(data.result)
        }

        function find_button(layout, key) {
            var children = layout.children;
            for(var i = 0; i < children.length; ++i)
                if(children[i].evalText === key)
                    return children[i];
            return false;
        }

        function compare_result(expected) {
            var model = root.children[0].model
            compare(model.get(model.count - 1).result, expected)
        }
    }

    TestCase {
        name: "gui-react"
        when: windowShown

        function test_keyboardReactions() {
            var keypad = root.children[1].children[0]
            var button0 = keypad.children[9]
            var textColour = button0.children[0].color
            var initialColour = textColour.toString()

            keyPress(Qt.Key_0)
            verify(textColour.toString() !== initialColour)

            keyRelease(Qt.Key_0)
            compare(textColour.toString(), initialColour)
        }

        function test_mouseReactions() {
            var keypad = root.children[1].children[0]
            var button0 = keypad.children[9]
            var textColour = button0.children[0].color
            var initialColour = textColour.toString()

            mousePress(button0, button0.width / 2, button0.height / 2)
            verify(textColour.toString() !== initialColour)

            mouseRelease(button0, button0.width / 2, button0.height / 2)
            compare(textColour.toString(), initialColour)
        }

        function cleanup() {
            root.children[0].model.clear()
        }
    }
}
