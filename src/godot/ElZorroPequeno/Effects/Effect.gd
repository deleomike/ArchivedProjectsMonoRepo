extends AnimatedSprite


func _ready():
	frame = 0
	
	connect("animation_finished", self, "_on_animation_finished")
	
	play("Animate")

func _on_animation_finished():
	# when this animation finishes, the sprite will dissapear
	queue_free()
