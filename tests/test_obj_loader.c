#include "test.h"

Test(obj_files, ignoring_unrecognized_lines)
{
	t_obj_loader	loader;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/Gibberish.obj");
	cr_assert(eq(int, loader.ignored_lines, 5));
}

Test(obj_files, vertex_records)
{
	t_obj_loader	loader;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/VertexRecords.obj");
	cr_assert(eq(int, loader.vertices_count, 4));
	cr_assert(eq(dbl, loader.vertices[0].x, -1));
	cr_assert(eq(dbl, loader.vertices[0].y, 1));
	cr_assert(eq(dbl, loader.vertices[0].z, 0));
	cr_assert(eq(dbl, loader.vertices[1].x, -1));
	cr_assert(eq(dbl, loader.vertices[1].y, 0.5));
	cr_assert(eq(dbl, loader.vertices[1].z, 0));
	cr_assert(eq(dbl, loader.vertices[2].x, 1));
	cr_assert(eq(dbl, loader.vertices[2].y, 0));
	cr_assert(eq(dbl, loader.vertices[2].z, 0));
	cr_assert(eq(dbl, loader.vertices[3].x, 1));
	cr_assert(eq(dbl, loader.vertices[3].y, 1));
  cr_assert(eq(dbl, loader.vertices[3].z, 0));
}

Test(obj_files, parsing_triangle_faces)
{
	t_obj_loader	loader;
	t_shape			group;
	t_shape			*t1;
	t_shape			*t2;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/TriangleFaces.obj");
	group = loader.default_group;
	t1 = group.g->shape;
	t2 = group.g->next->shape;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
}

Test(obj_files, tringulating_polygons)
{
	t_obj_loader	loader;
	t_shape			group;
	t_shape			*t1;
	t_shape			*t2;
	t_shape			*t3;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/TriangulatingPolygons.obj");
	group = loader.default_group;
	t1 = group.g->shape;
	t2 = group.g->next->shape;
	t3 = group.g->next->next->shape;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(ptr, t3, &loader.triangles[2]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
	cr_assert(eq(dbl, t3->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t3->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t3->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t3->tri.p2.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t3->tri.p2.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t3->tri.p2.z, loader.vertices[3].z));
	cr_assert(eq(dbl, t3->tri.p3.x, loader.vertices[4].x));
	cr_assert(eq(dbl, t3->tri.p3.y, loader.vertices[4].y));
	cr_assert(eq(dbl, t3->tri.p3.z, loader.vertices[4].z));
}
