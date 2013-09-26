import QtQuick 2.0
import QtTest 1.0
import "tests"

Item {
    Unit {}

    TestCase {
        name: "OtherTests"

        function test_string() {
            compare(" ", ' ')
        }
    }
}
