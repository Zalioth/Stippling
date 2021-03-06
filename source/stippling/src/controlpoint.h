/**
 * @file controlpoint.h
 * @brief ControlPoint header file
 *
 * @version 0.1
 * @author José Ignacio Carmona Villegas <joseicv@correo.ugr.es>
 * @date 4/November/2013
 *
 * @thanks Germán Arroyo Moreno <arroyo@ugr.es>
 *
 */

#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>

#include <QDomDocument>
#include <math.h>

#include "glentity.h"
#include "util.h"
#include "enums.h"
#include "triangle.h"

#define CONSTRAINT_NONE 0
#define CONSTRAINT_TRANSLATION_X 1
#define CONSTRAINT_TRANSLATION_Y 2
#define CONSTRAINT_TRANSLATION_Z 4
#define CONSTRAINT_RESIZE_X 8
#define CONSTRAINT_RESIZE_Y 16
#define CONSTRAINT_RESIZE_Z 32
#define CONSTRAINT_ROTATION_X 64
#define CONSTRAINT_ROTATION_Y 128
#define CONSTRAINT_ROTATION_Z 256
#define CONSTRAINT_SCALE_X 512
#define CONSTRAINT_SCALE_Y 1024
#define CONSTRAINT_SCALE_Z 2048

/**
 * @brief Control Point class
 * Represents a control point for an Entity3D. Keeps track of a local (to the entity) position and has interaction restrictions.
 */
class ControlPoint
{
private:
    GLEntity _entity; /**< Graphical entity that represents the CP's sphere. */
    float _radius; /**< Radius of the CP (in pixels). */
    glm::vec3 _localPos; /**< Local position of the CP (local to the coord system defined by the entity it describes. */
    unsigned int _constraints; /**< Mask of constraints that the CP is subject to. */
    static const int _trianglesPerCircle = 18; /**< Deprecated! Resolution of the circle generated by generateCircle(). */

    int numberOfTriangles; /**< Number of triangles that will be rendered by the graphical entity. */
    int numberOfVertices; /**< Number of vertices that will be rendered by the graphical entity. */
    int numberOfValues; /**< Number of values that will be rendered by the graphical entity (This is the size of the array triangles). */
    GLfloat * triangles; /**< Array that contains the geometry used to initialize the graphical entity. */

    void initialize(int id, glm::vec3 selectionColor, unsigned int constraints, glm::vec3 localPos, float radius,
                    GLuint renderShader, GLuint selectionShader);

public:
    /**
     * @brief Default constructor.
     * Required to be able to use the CP in stack.
     * It doesn't actually initialize a renderable CP.
     */
    ControlPoint();
    /**
     * @brief Constructor.
     * Constructs and initializes a CP using the provided information.
     * @param id Control Point id. Used to univocally identify the CP among other entities in the selection process.
     * @param selectionColor Color used in the selection process. It must be decodeable back to the id.
     * @param constraints Mask of constraints to be assigned.
     * @param localPos Local position to be assigned.
     * @param radius Radius of the CP to be rendered.
     * @param renderShader Shader used to render the CP in normal mode.
     * @param selectionShader Shader used to render the CP in selection mode.
     */
    ControlPoint(int id, glm::vec3 selectionColor, unsigned int constraints, glm::vec3 localPos, float radius,
                 GLuint renderShader, GLuint selectionShader);

    /**
     * @brief XML Constructor
     * @param id
     * @param selectionColor
     * @param node
     * @param radius
     * @param renderShader
     * @param selectionShader
     */
    ControlPoint(int id, glm::vec3 selectionColor, QDomNode node, float radius,
                 GLuint renderShader, GLuint selectionShader);

    // Getters
    int id() const;
    unsigned int constraints() const;
    float radius() const;
    glm::vec3 localPos() const;

    // Testers
    /**
     * @brief Tests if the CP is constrainted exactly as the passed mask.
     * @param constraint Constraint mask to test against.
     * @return Truth value that indicates the result of the test.
     */
    bool isConstraintedAs(const unsigned int constraint) const;
    /**
     * @brief Tests if the CP is constrainted as any of the flags that compose the passed mask.
     * @param constraint Constraint mask to test against.
     * @return Truth value that indicates the result of the test.
     */
    bool isConstraintedAsAny(const unsigned int constraint) const;

    // Setters
    void setRadius(float radius);
    void setColor(glm::vec3 color);
    void setColorByConstraint(glm::vec3 position, glm::vec3 resize, glm::vec3 rotate, glm::vec3 scale);
    void setLocalPos(glm::vec3 localPos);

    /**
     * @brief Renders the CP.
     * @param selectionMode Indicates if the CP should be rendered normally or using the selectionColor (in selection mode).
     * @param view View matrix.
     * @param projection Projection matrix.
     * @param extModel External model matrix. Additional model matrix to be applied to the CP.
     */
    void paint(SelectionMode selectionMode, const glm::mat4 * view, const glm::mat4 * projection, const glm::mat4 * extModel);

    QDomElement toXML(QDomDocument * doc) const;

private:
    // DEPRECATED! Kept only in case it's needed in the future. Now the CPs are rendered using spheres.
    GLfloat * generateCircle(const float radius, const int numberOfTriangles, const int valuesPerVertex = 3);

    /**
     * @brief Generates an Ico-Sphere with the specified radius and resolution.
     * Sets the values of the numberOfValues property and reserves and initializes memory for the triangles array.
     * The Ico-Sphere is generated via fractal subdivision of a icosahedron. Resolution level 0 produces an icosahedron.
     * Greater resolution levels will further approximate the sphere, but will also cost more memory and computational power.
     * @param radius Radius of the CP to be rendered.
     * @param resolution Resolution of the Ico-Sphere to be generated.
     */
    void generateIcoSphere(const float radius, const int resolution);
};

#endif // CONTROLPOINT_H
