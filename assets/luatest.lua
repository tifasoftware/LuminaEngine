function onCall()
    luminaPic = lumina.loadTexture("lumina_dialog.png")
    entityPic = lumina.loadTexture("enph.png")

    lumina.say("Entities Work", "Test Entity", entityPic)
    lumina.say("Awesome!", "Lumina", luminaPic)
    lumina.say("Isn't it nice that we can talk to each other!", "Test Entity", entityPic)
    lumina.say("You bet!", "Lumina", luminaPic)

    lumina.unloadTexture(luminaPic)
    lumina.unloadTexture(entityPic)
end
