#include "6DOFConstraint.h"
#include "NewtonPhysicsWorld.h"
#include "UrhoNewtonConversions.h"
#include "dCustom6dof.h"

#include "Urho3D/Core/Context.h"




namespace Urho3D {


    NewtonSixDofConstraint::NewtonSixDofConstraint(Context* context) : NewtonConstraint(context)
    {

    }

    NewtonSixDofConstraint::~NewtonSixDofConstraint()
    {

    }

    void NewtonSixDofConstraint::RegisterObject(Context* context)
    {
        context->RegisterFactory<NewtonSixDofConstraint>(DEF_PHYSICS_CATEGORY.c_str());


        URHO3D_COPY_BASE_ATTRIBUTES(NewtonConstraint);
    }

    void NewtonSixDofConstraint::SetPitchLimits(float minLimit, float maxLimit)
    {
        if (pitchLimits_ != Vector2(minLimit, maxLimit)) {
            pitchLimits_.x_ = minLimit;
            pitchLimits_.y_ = maxLimit;
            if (newtonJoint_)
            {
                static_cast<dCustom6dof*>(newtonJoint_)->SetPitchLimits(pitchLimits_.x_, pitchLimits_.y_);
            }
            else
                MarkDirty();
        }
    }

    void NewtonSixDofConstraint::SetPitchLimits(const Vector3& limits)
    {
        SetPitchLimits(limits.x_, limits.y_);
    }

    void NewtonSixDofConstraint::SetYawLimits(float minLimit, float maxLimit)
    {
        if (yawLimits_ != Vector2(minLimit, maxLimit)) {
            yawLimits_.x_ = minLimit;
            yawLimits_.y_ = maxLimit;
            if (newtonJoint_)
            {
                static_cast<dCustom6dof*>(newtonJoint_)->SetYawLimits(yawLimits_.x_, yawLimits_.y_);
            }
            else
                MarkDirty();
        }
    }

    void NewtonSixDofConstraint::SetYawLimits(const Vector3& limits)
    {
        SetYawLimits(limits.x_, limits.y_);
    }

    void NewtonSixDofConstraint::SetRollLimits(float minLimit, float maxLimit)
    {
        if (rollLimits_ != Vector2(minLimit, maxLimit)) {
            rollLimits_.x_ = minLimit;
            rollLimits_.y_ = maxLimit;
            if (newtonJoint_)
            {
                static_cast<dCustom6dof*>(newtonJoint_)->SetRollLimits(rollLimits_.x_, rollLimits_.y_);
            }
            else
                MarkDirty();
        }
    }

    void NewtonSixDofConstraint::SetRollLimits(const Vector3& limits)
    {
        SetRollLimits(limits.x_, limits.y_);
    }

    void NewtonSixDofConstraint::DrawDebugGeometry(DebugRenderer* debug, bool depthTest)
    {
        NewtonConstraint::DrawDebugGeometry(debug, depthTest);
    }

    void NewtonSixDofConstraint::buildConstraint()
    {
        newtonJoint_ = new dCustom6dof(UrhoToNewton(GetOwnNewtonBuildWorldFrame()), UrhoToNewton(GetOtherNewtonBuildWorldFrame()), GetOwnNewtonBody(), GetOtherNewtonBody());




    }

    bool NewtonSixDofConstraint::applyAllJointParams()
    {
        if (!NewtonConstraint::applyAllJointParams())
            return false;

        static_cast<dCustom6dof*>(newtonJoint_)->SetLinearLimits(dVector(M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE)*-1.0f, dVector(M_LARGE_VALUE, M_LARGE_VALUE, M_LARGE_VALUE));
        static_cast<dCustom6dof*>(newtonJoint_)->SetPitchLimits(pitchLimits_.x_ * dDegreeToRad, pitchLimits_.y_* dDegreeToRad);
        static_cast<dCustom6dof*>(newtonJoint_)->SetYawLimits(yawLimits_.x_* dDegreeToRad, yawLimits_.y_* dDegreeToRad);
        static_cast<dCustom6dof*>(newtonJoint_)->SetRollLimits(rollLimits_.x_* dDegreeToRad, rollLimits_.y_* dDegreeToRad);

        return true;
    }

}
