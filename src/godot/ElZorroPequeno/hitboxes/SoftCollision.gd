extends Area2D

# detect if it is overlapping something, and signal a push vector

func is_colliding():
	var areas = get_overlapping_areas()
	return areas.size() > 0
	
	
func get_push_vector():
	var areas = get_overlapping_areas()
	var push_vector = Vector2.ZERO
	
	if is_colliding():
		# get first area we are colliding with
		# helps to optimize by ignoring others
		var area = areas[0]
		push_vector = area.global_position.direction_to(global_position)
		push_vector = push_vector.normalized()
	
	return push_vector
	
