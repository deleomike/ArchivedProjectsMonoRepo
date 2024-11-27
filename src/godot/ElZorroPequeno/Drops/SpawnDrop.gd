extends Node2D

export(float) var SPAWN_CHANCE = 0.1
export(PackedScene) var ITEM = preload("res://Drops/HealthDrop.tscn")

func roll_for_spawn():
	var prob = rand_range(0, 1)
	
	if prob <= SPAWN_CHANCE:
		var main = get_tree().current_scene
		var item = ITEM.instance()
		item.position = global_position
		main.call_deferred("add_child", item)



func _on_SpawnDrop_tree_exiting():
	roll_for_spawn()
