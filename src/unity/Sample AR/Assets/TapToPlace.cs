using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;
using UnityEngine.XR.ARSubsystems;


public class TapToPlace : MonoBehaviour
{
    //Remove all reference points created
    public void RemoveAllAnchors()
    {
        foreach (var anchor in m_Anchors)
        {
            anchor.destroyOnRemoval = true;
            m_AnchorManager.RemoveAnchor(anchor);
        }
        m_Anchors.Clear();
    }


    void Awake()
    {
        m_RaycastManager = GetComponent<ARRaycastManager>();
        m_AnchorManager = GetComponent<ARAnchorManager>();
        //m_ReferencePointManager = GetComponent<ARReferencePointManager>();
        m_PlaneManager = GetComponent<ARPlaneManager>();
        m_Anchors = new List<ARAnchor>();
    }


    bool TryGetTouchPosition(out Vector2 touchPosition)
    {
        if (Input.touchCount > 0)
        {
            touchPosition = Input.GetTouch(0).position;
            return true;
        }

        touchPosition = default;
        return false;
    }

    // Update is called once per frame
    void Update()
    {
        if (!TryGetTouchPosition(out Vector2 touchPosition))
            return;

        if (m_RaycastManager.Raycast(touchPosition, s_Hits, TrackableType.PlaneWithinPolygon))
        {
            // Raycast hits are sorted by distance, so the first one
            // will be the closest hit.
            var hitPose = s_Hits[0].pose;
            TrackableId planeId = s_Hits[0].trackableId; //get the ID of the plane hit by the raycast
            var anchor = m_AnchorManager.AttachAnchor(m_PlaneManager.GetPlane(planeId), hitPose);
            if (anchor != null)
            {
                RemoveAllAnchors();
                m_Anchors.Add(anchor);
            }
        }
    }

    static List<ARRaycastHit> s_Hits = new List<ARRaycastHit>();

    ARRaycastManager m_RaycastManager;
    ARAnchorManager m_AnchorManager;
    List<ARAnchor> m_Anchors;
    ARPlaneManager m_PlaneManager;

    // Start is called before the first frame update
    void Start()
    {
        
    }
}
