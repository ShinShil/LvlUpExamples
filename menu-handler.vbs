const WORKER_VIEW = "WorkerView"
const WORKERS_VIEW = "WorkersView"
const MARK_ACTIVE_TASK = "MarkActiveTask"
const UNMARK_ACTIVE_TASK = "UnmarkActiveTask"

Sub WorkerList_ExecutionHandler(oSender, oEventArgs)
    If oEventArgs.Action = WORKER_VIEW Then
        WorkerView oSender
    ElseIf oEventArgs.Action = WORKERS_VIEW Then
        WorkersView   
    End If
End Sub

'Subs in lp-workers-edit.vbs, because they need oEditor
Sub usr_Tasks_ListMenu_ExecutionHandler(oSender, oMenuEventArgs) 
    Dim sObjectID 'task ID that was blue, when menuexecutionhandler excuted 
    sObjectID = oMenuEventArgs.Menu.Macros.Item("ObjectID")
    If (HasValue(sObjectID)) Then 
        If oMenuEventArgs.Action = MARK_ACTIVE_TASK Then 'oSender.ValueID; To for visibility - just cmp valuID and ActiveTaskID
            markActiveTask sObjectID
        ElseIf oMenuEventArgs.Action = UNMARK_ACTIVE_TASK Then
            unmarkActiveTask sObjectID
        End If
    End If
End Sub

Sub usr_Tasks_ListMenu_VisibilityHandler(oSender, oMenuEventArgs)
    Dim sObjectID 'task ID that was blue, when menuexecutionhandler excuted
    Dim bHidden 'признак спрятанного элемента
    Dim bDisabled 'признак неактивного элемента
    Dim bProcess 'признак обрабатываемого элемента
    Dim sType 'Тип task
    Dim sActiveTaskID

    sType = oMenuEventArgs.Menu.Macros.Item("ObjectType")
    sObjectID = oMenuEventArgs.Menu.Macros.Item("ObjectID")
    Set oActiveTask = g_oEditor.Pool.GetXmlProperty(g_oEditor.XmlObject, "ActiveTaskID")
    If (HasValue(oActiveTask.firstChild)) Then
        sActiveTaskID = oActiveTask.selectSingleNode("TasksNick").getAttribute("oid")
    Else
        sActiveTaskID = "false"
    End If
    For Each oNode In oMenuEventArgs.ActiveMenuItems
        ' установим атрибуты на пункте меню, чтобы oMenu.SetMenuItemsAccessRights смог увязать запросы на проверку прав и пункты меню (при проставлении флага disabled)
		oNode.setAttribute "type", sType
		If Not IsNull(sObjectID) Then _
			oNode.setAttribute "oid",  sObjectID
				
		bHidden = Empty
		bDisabled = Empty
		bProcess = False
        Select Case oNode.getAttribute("action")
            Case MARK_ACTIVE_TASK
                If (Not HasValue(sObjectID)) Then
                    oNode.SetAttribute "hidden", 1
                    oNode.SetAttribute "disabled", 1
                ElseIf (sObjectID = sActiveTaskID) Then
                    oNode.SetAttribute "hidden", 1
                    oNode.SetAttribute "disabled", 1
                Else 
                    oNode.RemoveAttribute "hidden"
                    oNode.RemoveAttribute "disabled"
                End If
            CASE UNMARK_ACTIVE_TASK
                If (Not HasValue(sObjectID)) Then
                    oNode.SetAttribute "hidden", 1
                    oNode.SetAttribute "disabled", 1
                ElseIf (sObjectID = sActiveTaskID) Then
                    oNode.RemoveAttribute "hidden"
                    oNode.RemoveAttribute "disabled"
                Else 
                    oNode.SetAttribute "hidden", 1
                    oNode.SetAttribute "disabled", 1
                End If
        End Select
    Next
End Sub

Sub WorkerView(oSender)
    Dim WorkerID 
    WorkerID = oSender.GetSelectedObjectID
    X_OpenReport "x-get-report.aspx?name=r-worker.xml&amp;WorkerID=" & WorkerID
End Sub

Sub WorkersView() 
    X_OpenReport "x-get-report.aspx?name=r-workers.xml"
End Sub
