extends Node2D

# The grass effect scene
const GrassEffect = preload("res://Effects/GrassEffect.tscn")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func create_grass_effect():
	
	# A grass effect node
	var grassEffect = GrassEffect.instance()
	
	# One way to do this
	# Root node of our current scene
	#	var world = get_tree().current_scene
	#
	#	world.add_child(grassEffect)
	#
	#	grassEffect.global_position = global_position
	
	var grass = get_parent()
	grass.add_child(grassEffect)
	grassEffect.position = self.position



func _on_HurtBox_area_entered(_area):
	create_grass_effect()
	queue_free()
