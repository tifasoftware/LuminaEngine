function onCall()
    luminaPic = lumina.loadTexture("lumina_dialog.png")
    entityPic = lumina.loadTexture("enph.png")
    entityName = "Test Entity"

    lumina.say("What do you want to try out?", entityName, entityPic)
    answer = lumina.ask("What do you want to try out?", "Lumina", luminaPic, "LTL Text", "Cinematic", "Battle", "Nothing")

    if answer == 1 then
        lumina.say("Regular <b>Bold</> <i>Italic</>", entityName, entityPic)
    elseif answer == 2 then
        lumina.say("Not here yet!", entityName, entityPic)
    elseif answer == 3 then
        lumina.startBattle()
    elseif answer == 4 then
        lumina.say("umm... okay.", entityName, entityPic)
    end

    lumina.unloadTexture(luminaPic)
    lumina.unloadTexture(entityPic)
end
