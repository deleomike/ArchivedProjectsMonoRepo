extends KinematicBody2D

var speed: int = 200
var velocity: Vector2 = Vector2(speed, 0)

var is_left: bool = true

onready var sprite: Sprite = get_node("Enemy")

func _physics_process(delta):
	"""
	If we press the right or left, this applies the physics
	
	This is called 60 times per minute
	delta: distance or time duration between each frame (1/60)
	"""
	
	var rot = 0.1
	
	if is_left:
		rot *= -1
	
	sprite.rotate(rot)
	
	var obj = move_and_collide(velocity * delta)
	
	if obj != null:
		if obj.collider.is_in_group("Tiles"):
			velocity.x = - velocity.x
			is_left = !is_left
		
	# applying the movements
	#velocity = move_and_slide(velocity, Vector2.UP)

