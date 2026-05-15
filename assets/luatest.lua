function onCall()
    luminaPic = lumina.loadTexture("lumina_dialog.png")
    entityPic = lumina.loadTexture("enph.png")

    lumina.say("Isn't it nice that we can talk to each other!", "Test Entity", entityPic)
    answer = lumina.ask("Isn't it nice?", "Lumina", luminaPic, "Yeah", "Nah", "Maybe", "I Don't Know")
    lumina.say("You said option #" .. answer, "Test Entity", entityPic)

    lumina.unloadTexture(luminaPic)
    lumina.unloadTexture(entityPic)
end
