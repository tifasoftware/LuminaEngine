function onCall()
    luminaPic = lumina.loadTexture("lumina_dialog.png")
    entityPic = lumina.loadTexture("enph.png")
    entityName = "Test Entity"

    lumina.say("Isn't it nice that we can talk to each other!", entityName, entityPic)
    answer = lumina.ask("Isn't it nice?", "Lumina", luminaPic, "Yeah", "Nah", "Maybe", "I Don't Know")

    if answer == 1 then
        lumina.say("I agree", entityName, entityPic)
    elseif answer == 2 then
        lumina.say("Well. Agree to disagree.", entityName, entityPic)
    elseif answer == 3 then
        lumina.say("Indecisive much?", entityName, entityPic)
    elseif answer == 4 then
        lumina.say("umm... okay.", entityName, entityPic)
    end

    lumina.unloadTexture(luminaPic)
    lumina.unloadTexture(entityPic)
end
