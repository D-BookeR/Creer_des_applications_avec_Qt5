import QtQuick 2.0
import QtTest 1.0
import "Calculator.js" as Calculator

Item {
    TestCase {
        name: "Calculator.js"

        function test_evalToUser_data() {
            return [{ input: "1+2", expected: "1+2" }, // No change
                    { input: "1-2", expected: "1–2" }, // ASCII - vs &#0150;
                    { input: "1*2", expected: "1×2" }, // * vs ×
                    { input: "1/2", expected: "1÷2" }];// / vs ÷
        }

        function test_evalToUser(data) {
            compare(Calculator.evalToUser(data.input), data.expected)
        }
    }
}
