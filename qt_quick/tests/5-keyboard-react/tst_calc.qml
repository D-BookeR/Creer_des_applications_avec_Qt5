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

        function init_data() {
            return [{ sequence: ['1', '+', '2'], result: 3 },
                    { sequence: ['3', '*', '4', '-', '5'], result: 7 },
                    { sequence: ['9', '/', '6'], result: 1.5},
                    { sequence: ['-', '8', '+', '7'], result: -1}]
        }

        function test_keyboard(data) {
            data.sequence.map(keyClick)
            keyClick(Qt.Key_Return)
            var model = root.children[0].model
            compare(model.get(model.count - 1).result, data.result)
        }
    }

    TestCase {
        name: "gui-react"
        when: windowShown

        function test_keyboardReactions() {
            var keypad = root.children[1].children[0]
            var button0 = keypad.children[9]
            var initialColour = button0.textColour.toString()

            keyPress(Qt.Key_0)
            verify(button0.textColour.toString() !== initialColour)

            keyRelease(Qt.Key_0)
            compare(button0.textColour.toString(), initialColour)
        }
    }
}
