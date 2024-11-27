extends RichTextLabel


var score = 0

func _reset_score():
	set_score(0)
	

func _increment_score():
	set_score(score + 1)


func set_score(new_score):
	score = new_score
	
	text = "Score: " + str(score)
	

# Called when the node enters the scene tree for the first time.
func _ready():
	var main_scene = get_tree().get_current_scene()
	set_score(0)
	
	main_scene.connect("reset", self, "_reset_score")
	main_scene.connect("increment_score", self, "_increment_score")


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
