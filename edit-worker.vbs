Dim g_oEditor
Dim g_oPool
Const ACTIVE_TASK_PRESENTATION = "Активная"
Const UNACTIVE_TASK_PRESENTATION = "Неактивная"


Sub usrXEditor_OnLoad(oSender, oEventArgs)
    Set g_oEditor = oSender
    Set Shell = CreateObject("Shell.Application")
    Dim locationForParse
    Dim Window
    For Each Window In Shell.Windows
        ' Make sure it's an Internet Explorer (iexplore) window...
        If InStr(1, Window.FullName, "iexplore.exe", vbTextCompare) > 0 Then
            ' Display the URL of the current page...
            locationForParse = Window.LocationUrl
        End If
    Next
    Set g_oPool = oSender.Pool
End Sub

Sub usrXEditor_OnPageStart(oSender, oEventArgs)
    setCaption g_oEditor.ObjectType & " from " & g_oEditor.QueryString.GetValue("listMetaname", "Unknown i:objects-list"), g_oEditor.CurrentPage.PageTitle
    If g_oEditor.CurrentPage.PageName = "main" Then
        setWorkerManagerProperties g_oEditor.Pool.GetPropertyValue(g_oEditor.XmlObject, "IsManager")
        g_oEditor.CurrentPage.EnablePropertyEditorEx g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "SalaryMultiplier")), false, true
        Set oCurrDepartment = g_oEditor.Pool.GetXmlProperty(g_oEditor.XmlObject, "DepartmentID")
        Dim departmentName : departmentName = "Нет отдела"
        If (HasValue(oCurrDepartment.firstChild)) Then
            departmentID = oCurrDepartment.selectSingleNode("DepartmentsNick").getAttribute("oid")
            departmentName = GetScalarValueFromDataSource("GetDepartmentNameById", Array("DepartmentID"), Array(departmentID))
        End If
        If (HasValue(document.all("button"))) Then
            document.all("button").InnerHtml = departmentName
        End If
        g_oPool.SetPropertyValue g_oPool.GetXmlProperty(g_oEditor.XmlObject, "Birthdate"), #5/12/1996#
        g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "Birthdate")).SetData
        
        If(Not HasValue(g_oPool.GetPropertyValue(g_oEditor.XmlObject, "EnterId"))) Then
            Dim tmp 
            tmp = GetScalarValueFromDataSource("GetUuidFromServer", Array(), Array())
            g_oPool.SetPropertyValue g_oPool.GetXmlProperty(g_oEditor.XmlObject, "EnterId"), tmp
            g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "EnterId")).SetData
        End If

    End If 
End Sub

Sub usr_Workers_IsManager_OnChanged(oSender, oEventArgs)
    If (oSender.Value) Then
        setWorkerManagerProperties(true)
    Else
        setWorkerManagerProperties(false)
    End If  
End Sub

Sub usr_Workers_Resources_OnAfterSelect(oSender, oEventArgs)
    'Получить объект сотрудника
    ' пробежать по Selection, для каждого: получить xml, добавить relation в 
    ' Msgbox "Hello"
End Sub

Sub usrXEditor_OnValidate(oEditor, oEventArgs)
    Set oWorkerCase = oEditor.XmlObject
    Dim dtBirthdate
        dtBirthdate = g_oPool.GetPropertyValue(oWorkerCase, "Birthdate")
        If Not IsNull(dtEnterRegister) Then
            If dtBirthdate > date() Then
                oEventArgs.ReturnValue = False
                oEventArgs.ErrorMessage = "Дата рождения не может быть больше сегодняшней даты"
                Exit Sub
            End If

            If (Year(date()) - Year(dtBirthdate)) < 16 Then
                oEventArgs.ReturnValue = False
                oEventArgs.ErrorMessage = "Мы принимаем сотрудников от 16 лет" ' Если дописать что возраст вычислен на основе разницы между датой рождения и текущей датой, то любой догадается как обойти'
                Exit Sub
            End If 
        Else
            oEventArgs.ReturnValue = False
            oEventArgs.ErrorMessage = "Укажите дату рождения"
            Exit Sub
        End If
End Sub

Function GetTaskState(oPool, taskID) 
    Set oWorkers = oPool.Xml.selectSingleNode("Workers")
    Dim ActiveTaskID
    Dim res
    Set TasksNick = oPool.GetXmlObjectByOPath(oWorkers, "ActiveTaskID")
    If (HasValue(TasksNick)) Then
        ActiveTaskID = TasksNick.getAttribute("oid")
        If (ActiveTaskID = taskID) Then
            res = ACTIVE_TASK_PRESENTATION
        Else 
            res = UNACTIVE_TASK_PRESENTATION
        End If
    Else
        res = UNACTIVE_TASK_PRESENTATION
    End If  
    GetTaskState = res
End Function

Sub markActiveTask(taskID)
    'If link is exist - delete
    Set oCurrActiveTask = g_oEditor.Pool.GetXmlProperty(g_oEditor.XmlObject, "ActiveTaskID")
    If (HasValue(oCurrActiveTask.firstChild)) Then
        Dim activeTaskIDToRemoveLink
        activeTaskIDToRemoveLink = oCurrActiveTask.selectSingleNode("TasksNick").getAttribute("oid")
        Set oActiveTaskToRemoveLink = X_GetObjectFromServer("TasksNick", activeTaskIdToRemoveLink, "")
        g_oEditor.Pool.RemoveRelation g_oEditor.XmlObject, "ActiveTaskID", oActiveTaskToRemoveLink
    End If
    Set oNewActiveTask = X_GetObjectFromServer("TasksNick", taskID, "")
    If (HasValue(oNewActiveTask)) Then
        g_oEditor.Pool.AddRelation g_oEditor.XmlObject, "ActiveTaskID", oNewActiveTask
        g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "Tasks")).SetData
    End If
End Sub

Sub unmarkActiveTask(taskID)
    Set oCurrActiveTask = g_oEditor.Pool.GetXmlProperty(g_oEditor.XmlObject, "ActiveTaskID")
    If (HasValue(oCurrActiveTask.firstChild)) Then
        activeTaskIDToRemoveLink = oCurrActiveTask.selectSingleNode("TasksNick").getAttribute("oid")
        Set oActiveTaskToRemoveLink = X_GetObjectFromServer("TasksNick", activeTaskIdToRemoveLink, "")
        g_oEditor.Pool.RemoveRelation g_oEditor.XmlObject, "ActiveTaskID", oActiveTaskToRemoveLink
        g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "Tasks")).SetData
    End If
End Sub

Sub SendToDepartment_OnClick()
'initPath - current OID и до родителя, OID - ObjectID
    Dim pathOid
    Dim sPath : sPath = ""
    Set oCurrDepartment = g_oPool.GetXmlProperty(g_oEditor.XmlObject, "DepartmentID").selectSingleNode("DepartmentsNick")
    If (HasValue(oCurrDepartment)) Then
        pathOid = oCurrDepartment.getAttribute("oid")
        Do While HasValue(pathOid)
            sPath = sPath & "|DepartmentsNick|"&pathOid
            pathOid = GetScalarValueFromDataSource("GetParentDepartmentOid", Array("ObjectID"), Array(pathOid))
        Loop
        sPath = Right(sPath, len(sPath) - 1)
    End If


    Set res = X_SelectFromTree("DepartmentsNickSelector",sPath,"","",Nothing)
    If (HasValue(res.Selection)) Then
        Dim departmentID
        Dim departmentIDToRemove
        Dim newVal
        departmentID = split(res.path,"|")(1)
        Set oCurrDepartment = g_oEditor.Pool.GetXmlProperty(g_oEditor.XmlObject, "DepartmentID")
        Set oNewDepartment = X_GetObjectFromServer("DepartmentsNick",departmentID,"")
        if (HasValue(oCurrDepartment.firstChild)) Then
            departmentIDToRemove = oCurrDepartment.selectSingleNode("DepartmentsNick").getAttribute("oid")
            Set oDepartmentToRemove = X_GetObjectFromServer("DepartmentsNick",departmentIDToRemove,"")
            g_oEditor.Pool.RemoveRelation g_oEditor.XmlObject, "DepartmentID", oDepartmentToRemove
        End if 
        g_oEditor.Pool.AddRelation g_oEditor.XmlObject, "DepartmentID", oNewDepartment
        Dim departmentName : departmentName = GetScalarValueFromDataSource("GetDepartmentNameById", Array("DepartmentID"), Array(departmentID))
        If (HasValue(document.all("button"))) Then
            document.all("button").InnerHtml = departmentName
        End If
    End If
End Sub

Sub setWorkerManagerProperties(bIsManager)
    bIsManager = bIsManager
    If (bIsManager) Then
        setManagerProperties
    Else
        setWorkerProperties
    End If
End Sub

Sub setManagerProperties()
    enableProjectID true
    setSalaryMultiplier 2
End Sub

Sub setWorkerProperties()
    enableProjectID false
    setSalaryMultiplier 1
End Sub

Sub enableProjectID(bEnable) 
    g_oEditor.CurrentPage.EnablePropertyEditorEx g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "ProjectID")), bEnable, true
End Sub

Sub setSalaryMultiplier(fValue)
    g_oPool.SetPropertyValue g_oPool.GetXmlProperty(g_oEditor.XmlObject, "SalaryMultiplier"), fValue
    g_oEditor.CurrentPage.GetPropertyEditor(g_oPool.GetXmlProperty(g_oEditor.XmlObject, "SalaryMultiplier")).SetData
End Sub

Sub setCaption(sEditorCaption, sPageCaption)
    g_oEditor.SetCaption sEditorCaption, sPageCaption
End Sub


