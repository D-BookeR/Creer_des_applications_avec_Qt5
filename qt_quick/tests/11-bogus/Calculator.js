function keyColour(text, colour) {
    var iterate = function (container) {
        for(var i = 0; i < container.children.length; ++i) {
            if(container.children[i].evalText == text) {
                if(colour)
                    container.children[i].textColour = colour
                else
                    container.children[i].colourDefault()
                break;
            }
        }
    }
    iterate(keyboard)
    iterate(operations)
}

function handleKey(causeEvaluation, text, colour) {
    if(colour) {
        keyColour(text, colour)
    }

    if(! causeEvaluation) {
        if (text !== "^") {
            main.computation += text
        } else {
            main.computation = "Math.pow(" + main.computation + ", "
            main.parentheses += 1
        }
    } else if(main.computation.length > 0) {
        while (main.parentheses > 0) {
            main.computation += ")";
            main.parentheses -= 1
        }

        model.append({
                         computation: main.computation,
                         result: eval(main.computation)
                     })
        main.computation = ""
        resultview.currentIndex = model.count - 1
    }
}

function evalToUser(string) {
    return string.replace("-", "–")
                 .replace("*", "×")
                 .replace("/", "÷")
}
