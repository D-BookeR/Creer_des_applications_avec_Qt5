function keyColour(text, colour) {
    for(var i = 0; i < grid.children.length; ++i) {
        if(grid.children[i].evalText == text) {
            if(colour)
                grid.children[i].textColour = colour
            else
                grid.children[i].colourDefault()
            break;
        }
    }
}

function handleKey(causeEvaluation, text, colour) {
    if(colour) {
        keyColour(text, colour)
    }

    if(! causeEvaluation) {
        main.computation += text
    } else if(main.computation.length > 0) {
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
