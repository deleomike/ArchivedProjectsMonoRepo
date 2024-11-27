extends Area2D

const HitEffect = preload("res://Effects/HitEffect.tscn")

var invincible = false setget set_invincible

signal invincibility_started
signal invincibility_ended

onready var timer = $Timer
onready var collisionShape = $CollisionShape2D

	
func set_invincible(value):
	invincible = value
	
#	print("Setting Inv ", value)
	
	if invincible:
		emit_signal("invincibility_started")
	else:
		emit_signal("invincibility_ended")
		
func start_invincibility(duration):
	self.invincible = true
#	print("Start inv for ", get_parent())
	timer.start(duration)
	
func create_hit_effect():
	var effect = HitEffect.instance()
	var main = get_tree().current_scene

	main.add_child(effect)
	effect.global_position = global_position


func _on_Timer_timeout():
	# setter only activated on self call
	# Cause of recursion
#	print("timeout")
	self.invincible = false


func _on_HurtBox_invincibility_started():
#	print("Invincibility Start ", get_parent())
	collisionShape.set_deferred("disabled", true)
	set_deferred("monitoring", false)


func _on_HurtBox_invincibility_ended():
#	print("Invincibility End ", get_parent())
	collisionShape.set_deferred("disabled", false)
	set_deferred("monitoring", true)

