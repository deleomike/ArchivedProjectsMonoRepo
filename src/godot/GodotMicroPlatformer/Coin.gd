extends StaticBody2D


func collected():
	hide()
	set_physics_process(false)
	get_node("CollisionShape2D").disabled = true
	

func reset():
	set_physics_process(true)
	show()
	get_node("CollisionShape2D").disabled = false


# Called when the node enters the scene tree for the first time.
func _ready():
	var main_scene = get_tree().get_current_scene()
	
	main_scene.connect("reset", self, "reset")
	main_scene.connect("reset", self, "reset")


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
