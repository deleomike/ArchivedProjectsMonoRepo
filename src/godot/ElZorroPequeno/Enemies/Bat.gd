extends KinematicBody2D


const EnemyDeathEffect = preload("res://Effects/EnemyDeathEffect.tscn")

export var ACCELERATION = 500
export var MAX_SPEED = 50
export var FRICTION = 200
export var WANDER_TARGET_RANGE = 4
export var KNOCKBACK = 150

enum {
	IDLE,
	WANDER,
	CHASE
}

var state = CHASE
var velocity = Vector2.ZERO
var knockback = Vector2.ZERO

onready var animatedSprite = $AnimatedSprite
onready var stats = $Stats
onready var playerDetectionZone = $PlayerDetectionZone
onready var hurtBox = $HurtBox
onready var softCollision = $SoftCollision
onready var wanderController = $WanderController
onready var blinkAnimationController = $BlinkAnimationPlayer


func _ready():
	print(stats.health)
	
	var random_frame = randi() % animatedSprite.frames.get_frame_count("Animate")
	
	animatedSprite.frame = random_frame
	
	state = pick_random_state()


func _physics_process(delta):
	knockback = knockback.move_toward(Vector2.ZERO, FRICTION * delta)
	knockback = move_and_slide(knockback)
	
	match state:
		IDLE:
			velocity = velocity.move_toward(Vector2.ZERO, FRICTION * delta)
			
			seek_player()
			
			check_for_new_state()
		WANDER:
			seek_player()
			
			accelerate_towards_point(wanderController.target_position, delta)
			
			if global_position.distance_to(wanderController.target_position) <= WANDER_TARGET_RANGE:
				state = pick_random_state()
				wanderController.start_wander_timer(rand_range(1, 3))
			
		CHASE:
			var player = playerDetectionZone.player
			
			# TODO: shouldnt this be call down/signal up?
			# This probably ought to be a signal connection
			# to check for player null
			if playerDetectionZone.can_see_player():
				accelerate_towards_point(player.position, delta)
			else:
				state = IDLE
			
	if softCollision.is_colliding():
		velocity += softCollision.get_push_vector() * delta * 100
		
	velocity = move_and_slide(velocity)


func accelerate_towards_point(point, delta):
	var direction = global_position.direction_to(point)
	velocity = velocity.move_toward(direction * MAX_SPEED, ACCELERATION * delta)
	animatedSprite.flip_h = velocity.x < 0


func check_for_new_state():
	if wanderController.get_time_left() == 0:
		state = pick_random_state()
		wanderController.start_wander_timer(rand_range(1, 3))


func seek_player():
	if playerDetectionZone.can_see_player():
		state = CHASE
		

func pick_random_state(state_list=[IDLE, WANDER]):
	state_list.shuffle()
	
	return state_list.pop_front()


func _on_HurtBox_area_entered(area):
	stats.health -= area.damage

	knockback = area.knockback_vector * KNOCKBACK
	hurtBox.start_invincibility(0.1)
	hurtBox.create_hit_effect()


func _on_Stats_no_health():
	queue_free()
	var enemyDeathEffect = EnemyDeathEffect.instance()
	get_parent().add_child(enemyDeathEffect)
	
	enemyDeathEffect.global_position = global_position


func _on_HurtBox_invincibility_started():
	blinkAnimationController.play("Start")


func _on_HurtBox_invincibility_ended():
	blinkAnimationController.play("Stop")
